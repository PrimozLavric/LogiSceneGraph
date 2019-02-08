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

#ifndef LSG_ACCELERATORS_BVH_SPLIT_BVH_BUILDER_H
#define LSG_ACCELERATORS_BVH_SPLIT_BVH_BUILDER_H
#include "lsg/accelerators/BVH/BVHBuilder.h"
#include <array>
#include "lsg/accelerators/BVH/TriangleAccessor.h"

namespace lsg {
namespace bvh {

struct SplitBVHConfig {
  /**
   * Maximum depth of the BVH where spatial split will still be used.
   */
  float split_alpha = 1.0e-5;;

  /**
   * Maximum depth of the BVH where spatial split will still be used.
   */
  size_t max_spatial_depth = 48;

  /**
   * Number of spatial bins per node in each axis.
   */
  size_t num_spatial_bins = 128;
};

#pragma region StateStructures
/**
 * @brief Holds information about an object split of the BVH node.
 */
struct SpatialSplit final {
	/**
	 * SAH cost of the split.
	 */
	float sah;

	/**
	 * Axis of the split.
	 */
	size_t axis;

	/**
	 * Position of the split.
	 */
	size_t position;
};

/**
 * @brief Holds info about a spatial bin.
 */
struct SpatialBin final {
	/**
	 * Bounding box of the bin.
	 */
	AABB bounds;

	/**
	 * Number of triangles entering the bin.
	 */
	size_t enter;

	/**
	 * Number of triangles leaving the bin.
	 */
	size_t exit;
};
#pragma endregion 

template <typename T>
class SplitBVHBuilder : public BVHBuilder<T> {
public:
  explicit SplitBVHBuilder(SAHFunction sha_function = SAHFunction(),
                           const BVHConfig& bvh_config = BVHConfig(),
                           const SplitBVHConfig& split_config = SplitBVHConfig());

  Shared<BVH<T>> process(const TriangleAccessor<T>& triangle_accessor);


  virtual ~SplitBVHBuilder() = default;
protected:
  /**
   * Declare base class members (this is required because base class is a template).
   */
  using BVHBuilder<T>::compareReferences;

  using BVHBuilder<T>::process;
  using BVHBuilder<T>::createLeaf;
  using BVHBuilder<T>::findObjectSplit;
  using BVHBuilder<T>::performObjectSplit;

  using BVHBuilder<T>::sha_function_;
  using BVHBuilder<T>::config_;
  using BVHBuilder<T>::t_reference_stack_;
  using BVHBuilder<T>::t_right_bounds_;
  using BVHBuilder<T>::t_nodes_;
  using BVHBuilder<T>::t_prim_indices_;

  uint32_t buildNode(const NodeSpec& spec, size_t level) override {
	  // If we have a small enough set or we've reached max allowed depth - Create a leaf.
	  if (spec.num_refs <= config_.min_leaf_size || level >= config_.max_depth) {
		  return createLeaf(spec);
	  }

	  const float area = spec.bounds.area();
	  const float leaf_sah = area * sha_function_.getPrimitiveCost(spec.num_refs);
	  const float node_sah = area * sha_function_.getNodeCost(2);

	  // Find best object split.
	  const ObjectSplit obj_split = findObjectSplit(spec, node_sah);
	  SpatialSplit spatial_split;

	  if (level < split_config_.max_spatial_depth) {
		  AABB overlap = obj_split.leftBounds;
		  overlap.intersect(obj_split.rightBounds);
		  if (overlap.area() >= t_min_overlap_) {
			  spatial_split = findSpatialSplit(spec, node_sah);
		  }
	  }

	  const float min_sah = std::min({ leaf_sah, obj_split.sah, spatial_split.sah });
	  // Create leaf if leaf SAH is the lowest and number of references does not exceed max leaf size.
	  if (min_sah == leaf_sah && spec.num_refs <= config_.max_leaf_size) {
		  return createLeaf(spec);
	  }

	  // Perform the split.
	  const std::pair<NodeSpec<T>, NodeSpec<T>> child_spec;
	  if (min_sah == spatial_split.sah) {
		  child_spec = performSpatialSplit(spec, spatial_split);
	  }

	  if ((child_spec.first.num_refs == 0u) || (child_spec.second.num_refs == 0u)) {
		  child_spec = performObjectSplit(spec, obj_split);
	  }

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

  SpatialSplit findSpatialSplit(const NodeSpec<T>& spec, float node_sah);

  std::pair<Reference<T>, Reference<T>> splitReference(const Reference<T>& ref, size_t axis, T position) const;

  /**
   * SplitBVH configuration.
   */
  SplitBVHConfig split_config_;

  /**
   * Minimum overlap of the left and right bounding box of the object split needed to make spatial split worth finding.
   */
  float t_min_overlap_;

  /**
   * Spatial bins.
   */
  std::array<std::vector<SpatialBin>, 3> t_spatial_bins_;

  /**
   * Triangle accessor.
   */
  const TriangleAccessor<T>* t_triangle_accessor_;
};


template <typename T>
SplitBVHBuilder<T>::SplitBVHBuilder(SAHFunction sha_function, const BVHConfig& bvh_config,
                                    const SplitBVHConfig& split_config)
  : BVHBuilder(sha_function, bvh_config),
    split_config_(split_config),
    t_min_overlap_(), 
    t_triangle_accessor_(nullptr) {
  for (size_t i = 0; i < 3u; i++) {
    t_spatial_bins_[i].resize(split_config_.num_spatial_bins);
  }
}

template <typename T>
Shared<BVH<T>> SplitBVHBuilder<T>::process(const TriangleAccessor<T>& triangle_accessor) {
	t_triangle_accessor_ = &triangle_accessor;
  t_reference_stack_.resize(t_triangle_accessor_->count());

  // Generate references and compute root node bounding box.
  NodeSpec<T> root_spec(t_triangle_accessor_->count());

  for (uint32_t i = 0; i < t_triangle_accessor_->count(); i++) {
    Triangle<T> tri = t_triangle_accessor_->getTriangle();
    t_reference_stack_[i].index = i;
    // Compute triangle bounding box.
    t_reference_stack_[i].bounds.expand(tri.a);
    t_reference_stack_[i].bounds.expand(tri.b);
    t_reference_stack_[i].bounds.expand(tri.c);

    root_spec.bounds.expand(t_reference_stack_[i].bounds);
  }

  t_min_overlap_ = root_spec.bounds.area() * split_config_.split_alpha;

  // We need cache for at most max(N - 1, num_spatial_bins) right bounds.
  t_right_bounds_.resize(std::max(root_spec.num_refs, split_config_.num_spatial_bins) - 1);

  // Clear nodes and primitive indices vectors and reserve.
  t_nodes_.clear();
  t_prim_indices_.clear();
  t_nodes_.reserve(t_right_bounds_.size());
  t_prim_indices_.reserve(t_right_bounds_.size());

  buildNode(root_spec, 0);
  return Shared<BVH<T>>::create(std::move(t_nodes_), std::move(t_prim_indices_));
}

template <typename T>
SpatialSplit SplitBVHBuilder<T>::findSpatialSplit(const NodeSpec<T>& spec, float node_sah) {
	glm::tvec3<T> origin = spec.bounds.min();
	glm::tvec3<T> bin_size = (spec.bounds.max() - origin) * (1.0f / static_cast<float>(split_config_.num_spatial_bins));
	glm::tvec3<T> inv_bin_size = 1.0f / bin_size;

  // Reset spatial bins.
  for (size_t axis = 0; axis < 3u; axis++) {
	  t_spatial_bins_[axis].clear();
	  t_spatial_bins_[axis].resize(split_config_.num_spatial_bins);
  }

  for (auto it = t_reference_stack_.begin() + (t_reference_stack_.size() - spec.num_refs); it != t_reference_stack_.end(); it++) {
	  const Reference<T>& ref = *it;
	  glm::tvec3<size_t> first_bin = glm::clamp(glm::tvec3<size_t>((ref.bounds.min() - origin) * inv_bin_size), 
		                                      glm::tvec3<size_t>(0u), glm::tvec3<size_t>(split_config_.num_spatial_bins - 1u));
	  glm::tvec3<size_t> last_bin = glm::clamp(glm::tvec3<size_t>((ref.bounds.max() - origin) * inv_bin_size), 
		                                      glm::tvec3<size_t>(0u), glm::tvec3<size_t>(split_config_.num_spatial_bins - 1u));

	  for (size_t axis = 0u; axis < 3u; axis++) {
		  Reference<T> current_ref = ref;

		  for (int i = firstBin[dim]; i < lastBin[dim]; i++)
		  {
			  Reference leftRef, rightRef;
			  splitReference(leftRef, rightRef, currRef, dim, origin[dim] + binSize[dim] * (F32)(i + 1));
			  t_spatial_bins_[axis][i].bounds.grow(leftRef.bounds);
			  //current_ref = rightRef;
		  }

		  t_spatial_bins_[axis][first_bin[axis]].enter++;
		  t_spatial_bins_[axis][last_bin[axis]].exit++;
		  t_spatial_bins_[axis][last_bin[axis]].bounds.grow(current_ref.bounds);
	  }
  }


}

template <typename T>
std::pair<Reference<T>, Reference<T>> SplitBVHBuilder<T>::splitReference(const Reference<T>& ref, size_t axis, T split_pos) const {
	Reference<T> left = ref;
	Reference<T> right = ref;

	Triangle<T> tri = t_triangle_accessor_->getTriangle(ref.index);

  // Loop over edges.
  for (size_t i = 0u; i < 3u; i++) {
	  const glm::tvec3<T>& v0 = tri[i];
	  const glm::tvec3<T>& v1 = tri[(i + 1u) % 3u];

	  // Insert vertex to the boxes it belongs to.
    if (v0[axis] <= split_pos) {
		  left.bounds.expand(v0);
    }
    if (v0[axis] >= split_pos) {
		  right.bounds.expand(v1);
    }

    // If edge intersects split plane insert interpolated vertex in both bounding boxes.
	  if ((v0[axis] < split_pos && v1[axis] > split_pos) || (v0[axis] > split_pos && v1[axis] < split_pos)) {
		  glm::tvec3<T> pt = glm::mix(v0, v1, glm::clamp((split_pos - v0[axis]) / (v1[axis] - v0[axis]), static_cast<T>(0.0), static_cast<T>(1.0));
		  left.bounds.expand(pt);
		  right.bounds.expand(pt);
	  }
  }

  return { left, right };
}


}
}

#endif  // LSG_ACCELERATORS_BVH_SPLIT_BVH_BUILDER_H