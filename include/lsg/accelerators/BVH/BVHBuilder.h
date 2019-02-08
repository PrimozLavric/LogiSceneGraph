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

#ifndef LSG_ACCELERATORS_BVH_BUILDER_H
#define LSG_ACCELERATORS_BVH_BUILDER_H

#include "lsg/math/AABB.h"
#include <vector>
#include <deque>
#include "lsg/accelerators/BVH/SAHFunction.h"
#include "lsg/core/Shared.h"
#include "lsg/accelerators/BVH/BVH.h"

namespace lsg {
namespace bvh {

/**
 * @brief SAH BVHBuilder configuration.
 */
struct BVHConfig {
	/**
	 * @brief Maximum depth of the BVH tree.
	 */
	size_t max_depth = 64;

	/**
	 * Minimum number of primitives in leaf.
	 */
	size_t min_leaf_size = 1u;

	/**
	 * Maximum number of primitives in leaf.
	 */
	size_t max_leaf_size = std::numeric_limits<size_t>::max();
};

#pragma region StateStructures 
/**
 * @brief Holds information about an object split of the BVH node.
 */
template <typename T>
struct ObjectSplit final {
	/**
	 * SAH cost of the split.
	 */
	float sah = std::numeric_limits<float>::max();

	/**
	 * Axis along which the primitives are sorted.
	 */
	size_t sort_axis = 0;

	/**
	 * Number of primitives in left child.
	 */
	size_t num_left = 0;

	/**
	 * Left child bounding box.
	 */
	AABB<T> left_bounds = {};

	/**
	 * Right child bounding box.
	 */
	AABB<T> right_bounds = {};
};

/**
 * @brief Structure that holds bounding box and index of the primitive.
 */
template <typename T>
struct Reference final {
	/**
	   * @brief Initializes primitive bounding box and index.
	   *
	   * @param	bounds  Bounding box of the primitive.
	   * @param	index   Index of the primitive.
	   */
	Reference(const AABB<T>& bounds, uint32_t index);

	/**
	 * Bounding box of the primitive.
	 */
	AABB<T> bounds;

	/**
	 * Index of the primitive.
	 */
	uint32_t index;
};

template <typename T>
Reference<T>::Reference(const AABB<T>& bounds, const uint32_t index)
	: bounds(bounds), index(index) {}

/**
 * @brief BVH node specification.
 */
template <typename T>
struct NodeSpec final {

	/**
	 * @brief	Initializes number of references and bounding box.
	 *
	 * @param	num_refs  Number of references on the reference stack.
	 * @param	bounds    Bounding box of this node.
	 */
	explicit NodeSpec(size_t num_refs, const AABB<T>& bounds = {});

	/**
	 * Number of references on the reference stack.
	 */
	size_t num_refs;

	/**
	 * Bounding box of this node.
	 */
	AABB<T> bounds;
};

template <typename T>
NodeSpec<T>::NodeSpec(const size_t num_refs, const AABB<T>& bounds)
	: num_refs(num_refs), bounds(bounds) {}

#pragma endregion 

/**
 * @brief Class that builds a BVH using SAH.
 */
template <typename T>
class BVHBuilder {
public:
  /**
   * @brief Initializes the builder with the given SHAFunction and configuration.
   * 
   * @param	sha_function  Function used to compute SHA cost.
   * @param	config        BVH Builder configuration.
   */
  explicit BVHBuilder(SAHFunction sha_function = SAHFunction(), const BVHConfig& config = BVHConfig());

  /**
   * @brief   Performs the build.
   * 
   * @return  Shared Bounding Volume Hierarchy object.
   */
	Shared<BVH<T>> process(const std::vector<AABB<T>>& bounding_boxes);

protected:
  /**
	 * @brief   Reference comparison function. Compares midpoints of reference bounding boxes.
	 * 
	 * @param   axis  Axis along which midpoints are compared.
	 * @param	  ref_a Reference A. 
	 * @param	  ref_b Reference B 
	 * @return	True if reference A comes before reference B.
	 */
	static bool compareReferences(size_t axis, const Reference<T>& ref_a, const Reference<T>& ref_b);

  /**
	 * @brief   Builds either an inner node or leaf node based on the SAH cost. In case of
	 *          the inner node it recurses into the child nodes (first right then left).
	 *          Note: recursion order is important because of the stack. 
	 * 
	 * @param	  spec  Node specification. 
	 * @param	  level Depth of the node.
	 * @return	Index of the node.
	 */
	virtual uint32_t buildNode(const NodeSpec<T>& spec, size_t level);

  /**
	 * @brief   Create leaf node and return its index.
	 * 
	 * @param   spec  Node specification. 
	 * @return	Index of the leaf node.
	 */
	uint32_t createLeaf(const NodeSpec<T>& spec);

  /**
	 * @brief   Finds the best object split for the node.
	 * 
	 * @param   spec      Node specification.
	 * @param   node_sah  Node traversal cost.
	 * @return	Best object split for the node.
	 */
	ObjectSplit<T> findObjectSplit(const NodeSpec<T>& spec, float node_sah);

  /**
	 * @brief   Performs the object split described by the given ObjectSplit structure.
	 * 
	 * @param   spec  Specification of the node that is being split.
	 * @param	  split Best object split description. 
	 * @return	Pair containing left (first) and right (second) node specification.
	 */
	std::pair<NodeSpec<T>, NodeSpec<T>> performObjectSplit(const NodeSpec<T>& spec, const ObjectSplit<T>& split);

  /**
   * Function used to compute SHA cost.
   */
	SAHFunction sha_function_;

  /**
   * BVH builder configuration.
   */
	BVHConfig config_;

  /**
   * Reference stack.
   */
	std::deque<Reference<T>> t_reference_stack_;

  /**
   * Used to store bounding boxes of all the possible right children.
   */
	std::vector<AABB<T>> t_right_bounds_;

  /**
   * Vector of nodes.
   */
	std::vector<typename BVH<T>::Node> t_nodes_;

  /**
   * Vector of primitive references.
   */
	std::vector<uint32_t> t_prim_indices_;
};

template <typename T>
BVHBuilder<T>::BVHBuilder(SAHFunction sha_function, const BVHConfig& config)
	: sha_function_(std::move(sha_function)), config_(config) {}

template <typename T>
Shared<BVH<T>> BVHBuilder<T>::process(const std::vector<AABB<T>>& bounding_boxes) {
	t_reference_stack_.clear();

	// Generate references and compute root node bounding box.
	NodeSpec root_spec(bounding_boxes.size());

	for (uint32_t i = 0; i < bounding_boxes.size(); i++) {
		t_reference_stack_.emplace_back(bounding_boxes[i], i);
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
	return Shared<BVH<T>>::create(std::move(t_nodes_), std::move(t_prim_indices_));
}

template <typename T>
bool BVHBuilder<T>::compareReferences(const size_t axis, const Reference<T>& ref_a, const Reference<T>& ref_b) {
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

template <typename T>
uint32_t BVHBuilder<T>::buildNode(const NodeSpec<T>& spec, const size_t level) {
	// If we have a small enough set or we've reached max allowed depth - Create a leaf.
	if (spec.num_refs <= config_.min_leaf_size || level >= config_.max_depth) {
		return createLeaf(spec);
	}

	const float area = spec.bounds.area();
	const float leaf_sah = area * sha_function_.getPrimitiveCost(spec.num_refs);
	const float node_sah = area * sha_function_.getNodeCost(2);

	// Find best object split.
	const ObjectSplit obj_split = findObjectSplit(spec, node_sah);

	const float min_sah = std::min(leaf_sah, obj_split.sah);
	// Create leaf if leaf SAH is the lowest and number of references does not exceed max leaf size.
	if (min_sah == leaf_sah && spec.num_refs <= config_.max_leaf_size) {
		return createLeaf(spec);
	}

	// Perform the split.
	const std::pair<NodeSpec<T>, NodeSpec<T>> child_spec = performObjectSplit(spec, obj_split);

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

template <typename T>
uint32_t BVHBuilder<T>::createLeaf(const NodeSpec<T>& spec) {
	// Take references that belong to this node of the stack and store primitive indices.
	for (size_t i = 0; i < spec.num_refs; i++) {
		t_prim_indices_.emplace_back(t_reference_stack_.back().index);
		t_reference_stack_.pop_back();
	}

	// Generate BVH node that points to generated stored indices.
	t_nodes_.emplace_back(spec.bounds, true);
	auto& node = t_nodes_.back();
	node.indices_range[0] = t_prim_indices_.size() - spec.num_refs;
	node.indices_range[1] = t_prim_indices_.size();

	return t_nodes_.size() - 1;
}

template <typename T>
ObjectSplit<T> BVHBuilder<T>::findObjectSplit(const NodeSpec<T>& spec, const float node_sah) {
	ObjectSplit<T> best_split;
	float best_tie_break = std::numeric_limits<float>::max();

	// Iterator that points to element where the node references begin.
	const auto ref_begin = t_reference_stack_.end() - spec.num_refs;

	for (size_t axis = 0u; axis < 3u; axis++) {
		// Sort along the axis.
		std::sort(ref_begin, t_reference_stack_.end(), std::bind(compareReferences, axis, std::placeholders::_1, std::placeholders::_2));

		// Compute bounds right to left.
		AABB bounds;

		for (size_t i = spec.num_refs - 1; i > 0; i--) {
			bounds.expand((ref_begin + i)->bounds);
			t_right_bounds_[i - 1] = bounds;
		}

		// Compute bounds left to right and select division with lowest SAH cost.
		bounds.reset();

		for (size_t i = 1; i < spec.num_refs; i++) {
			bounds.expand((ref_begin + i - 1)->bounds);
			const float sah = node_sah
				+ bounds.area() * sha_function_.getPrimitiveCost(i)
				+ t_right_bounds_[i - 1].area() * sha_function_.getPrimitiveCost(spec.num_refs - i);

			const float tie_break = std::pow(i, 2) + std::pow(static_cast<float>(spec.num_refs - i), 2);

			// Check if this division SAH is better than previous best.
			if (sah < best_split.sah || (sah == best_split.sah && tie_break < best_tie_break)) {
				best_split.sah = sah;
				best_split.sort_axis = axis;
				best_split.num_left = i;
				best_split.left_bounds = bounds;
				best_split.right_bounds = t_right_bounds_[i - 1];
				best_tie_break = tie_break;
			}
		}
	}

	return best_split;
}

template <typename T>
std::pair<NodeSpec<T>, NodeSpec<T>> BVHBuilder<T>::performObjectSplit(const NodeSpec<T>& spec, const ObjectSplit<T>& split) {
	// Iterator that points to element where the node references begin.
	const auto ref_begin = t_reference_stack_.end() - spec.num_refs;

	std::sort(ref_begin, t_reference_stack_.end(), std::bind(compareReferences, split.sort_axis, std::placeholders::_1, std::placeholders::_2));

	return std::make_pair(NodeSpec<T>(split.num_left, split.left_bounds),
		                    NodeSpec<T>(spec.num_refs - split.num_left, split.right_bounds));
}


}
}

#endif // LSG_ACCELERATORS_BVH_BUILDER_H
