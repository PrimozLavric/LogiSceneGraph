/**
 * Project LogiSceneGraph source code
 * Copyright (C) 2019 Primoz Lavric
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "lsg/accelerators/BVH/Builder.h"
#include <algorithm>
#include <functional>

namespace lsg {
namespace bvh {

Reference::Reference(const AABB& bounds, const uint32_t index)
  : bounds(bounds),
	  index(index) {}

NodeSpec::NodeSpec(const size_t num_refs, const AABB& bounds) 
  : num_refs(num_refs), bounds(bounds) {}

Builder::Builder(Platform platform, const Config& config)
  : platform_(std::move(platform)), config_(config) {}

Shared<BVH> Builder::process(const std::vector<AABB>& bounding_boxes) {
	reference_stack_.clear();

	// Generate references and compute root node bounding box.
	NodeSpec root_spec(bounding_boxes.size());

	for (uint32_t i = 0; i < bounding_boxes.size(); i++) {
		reference_stack_.emplace_back(bounding_boxes[i], i);
		root_spec.bounds.expand(bounding_boxes[i]);
	}

  // We need cache for at most N - 1 right bounds.
	t_right_bounds_.resize(root_spec.num_refs - 1);

	// Clear nodes and primitive indices vectors and reserve.
  t_nodes_.clear();
	t_prim_indices_.clear();
	t_nodes_.reserve(bounding_boxes.size());
	t_prim_indices_.reserve(bounding_boxes.size());

	buildNode(root_spec, 0);
	return Shared<BVH>::create(std::move(t_nodes_), std::move(t_prim_indices_));
}

bool Builder::sortReferences(const size_t axis, const Reference& ref_a, const Reference& ref_b) {
	// Compare midpoint (division by 2 is not necessary).
	const float ca = ref_a.bounds.min()[axis] + ref_a.bounds.max()[axis];
	const float cb = ref_b.bounds.min()[axis] + ref_b.bounds.max()[axis];

	if (ca > cb) {
		return true;
	}

	if (ca < cb) {
		return false;
	}

	return ref_a.index > ref_b.index;
}

uint32_t Builder::buildNode(const NodeSpec& spec, const size_t level) {
  // If we have a small enough set or we've reached max allowed depth - Create a leaf.
	if (spec.num_refs <= platform_.getMinLeafSize() || level >= config_.max_depth) {
		return createLeaf(spec);
	}

	const float area = spec.bounds.area();
  const float leaf_SAH = area * platform_.getPrimitiveCost(spec.num_refs);
  const float node_SAH = area * platform_.getNodeCost(2);

  // Find best object split.
  const ObjectSplit obj_split = findObjectSplit(spec, node_SAH);

  // TODO: Spatial split.

  const float minSAH = std::min(leaf_SAH, obj_split.SAH);
  // Create leaf if leaf SAH is the lowest and number of references does not exceed max leaf size.
  if (minSAH == leaf_SAH && spec.num_refs <= platform_.getMaxLeafSize()) {
	  return createLeaf(spec);
  }

  const std::pair<NodeSpec, NodeSpec> child_spec = performObjectSplit(spec, obj_split);

  // Create internal node.
  t_nodes_.emplace_back(spec.bounds, false);
  const uint32_t parent_idx = t_nodes_.size() - 1u;
  
  // Right child needs to be built first so that references are retrieved from stack in correct order.
  const uint32_t right_idx = buildNode(child_spec.second, level + 1);
  const uint32_t left_idx = buildNode(child_spec.first, level + 1);

  t_nodes_[parent_idx].child_indices[0] = left_idx;
  t_nodes_[parent_idx].child_indices[1] = right_idx;

  return parent_idx;
}

uint32_t Builder::createLeaf(const NodeSpec& spec) {

  for (size_t i = 0; i < spec.num_refs; i++) {
	  t_prim_indices_.emplace_back(reference_stack_.back().index);
	  reference_stack_.pop_back();
  }

  t_nodes_.emplace_back(spec.bounds, true);
  BVH::Node& node = t_nodes_.back();
  node.indices_range[0] = t_prim_indices_.size() - spec.num_refs;
  node.indices_range[1] = t_prim_indices_.size();

  return t_nodes_.size() - 1;
}

ObjectSplit Builder::findObjectSplit(const NodeSpec& spec, const float node_sah) {
	ObjectSplit best_split;

  // Iterator that points to element where the node references begin.
  const auto ref_begin = reference_stack_.end() - spec.num_refs;

	for (size_t axis = 0u; axis < 3u; axis++) {
    // Sort along the axis.
		std::sort(ref_begin, reference_stack_.end(), std::bind(Builder::sortReferences, axis, std::placeholders::_1, std::placeholders::_2));

    // Compute bounds right to left.
	  AABB bounds;

	  for (size_t i = spec.num_refs - 1; i > 0; i--) {
		  bounds.expand((ref_begin + i)->bounds);
		  t_right_bounds_[i - 1] = bounds;
    }

    // Compute bounds left to right and select division with lowest SAH cost.
	  bounds.reset();
	  AABB leftBounds;

	  for (size_t i = 1; i < spec.num_refs; i++) {
		  leftBounds.expand((ref_begin + i - 1)->bounds);
	    const float sah = node_sah 
	                    + leftBounds.area() * platform_.getPrimitiveCost(i) 
	                    + t_right_bounds_[i - 1].area() * platform_.getPrimitiveCost(spec.num_refs - i);

      // Check if this division SAH is better than previous best.
	    if (sah < best_split.SAH) {
		    best_split.SAH = sah;
		    best_split.sort_axis = axis;
			  best_split.num_left = i;
			  best_split.left_bounds = leftBounds;
			  best_split.right_bounds = t_right_bounds_[i - 1];
		  }
	  }
	}

	return best_split;
}

std::pair<NodeSpec, NodeSpec> Builder::performObjectSplit(const NodeSpec& spec, const ObjectSplit& split) {
	// Iterator that points to element where the node references begin.
	const auto ref_begin = reference_stack_.end() - spec.num_refs;

	std::sort(ref_begin, reference_stack_.end(), std::bind(Builder::sortReferences, split.sort_axis, std::placeholders::_1, std::placeholders::_2));

	return std::make_pair(NodeSpec(split.num_left, split.left_bounds),
		                    NodeSpec(spec.num_refs - split.num_left, split.right_bounds));
}


}
}