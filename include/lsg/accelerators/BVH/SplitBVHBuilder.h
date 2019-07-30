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
#include <array>
#include "lsg/accelerators/BVH/BVHBuilder.h"
#include "lsg/core/Ref.h"
#include "lsg/resources/Triangle.h"

namespace lsg {
namespace bvh {

struct SplitBVHConfig {
  /**
   * Maximum depth of the BVH where spatial split will still be used.
   */
  double split_alpha = 1.0e-5;
  ;

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
template <typename T>
struct SpatialSplit final {
  /**
   * SAH cost of the split.
   */
  float sah = std::numeric_limits<float>::max();

  /**
   * Axis of the split.
   */
  size_t axis = 0u;

  /**
   * Position of the split.
   */
  T position = T(0.0);
};

/**
 * @brief Holds info about a spatial bin.
 */
template <typename T>
struct SpatialBin final {
  /**
   * Bounding box of the bin.
   */
  AABB<T> bounds;

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
  explicit SplitBVHBuilder(const SAHFunction& sha_function = SAHFunction(), const BVHConfig& bvh_config = BVHConfig(),
                           const SplitBVHConfig& split_config = SplitBVHConfig());

  Ref<BVH<T>> process(const Ref<TriangleAccessor<glm::tvec3<T>>>& triangle_accessor);

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

  using BVHBuilder<T>::sah_function_;
  using BVHBuilder<T>::config_;
  using BVHBuilder<T>::t_reference_stack_;
  using BVHBuilder<T>::t_right_bounds_;
  using BVHBuilder<T>::t_nodes_;
  using BVHBuilder<T>::t_prim_indices_;

  uint32_t buildNode(const NodeSpec<T>& spec, size_t level) override;

  SpatialSplit<T> findSpatialSplit(const NodeSpec<T>& spec, float node_sah);

  std::pair<Reference<T>, Reference<T>> splitReference(const Reference<T>& ref, size_t axis, T split_pos) const;

  std::pair<NodeSpec<T>, NodeSpec<T>> performSpatialSplit(const NodeSpec<T>& spec, const SpatialSplit<T>& split);

  /**
   * SplitBVH configuration.
   */
  SplitBVHConfig split_config_;

  /**
   * Minimum overlap of the left and right bounding box of the object split needed to make spatial split worth finding.
   */
  T t_min_overlap_;

  /**
   * Spatial bins.
   */
  std::array<std::vector<SpatialBin<T>>, 3> t_spatial_bins_;

  /**
   * Triangle accessor.
   */
  Ref<TriangleAccessor<glm::tvec3<T>>> t_triangle_accessor_;
};

template <typename T>
SplitBVHBuilder<T>::SplitBVHBuilder(const SAHFunction& sha_function, const BVHConfig& bvh_config,
                                    const SplitBVHConfig& split_config)
  : BVHBuilder<T>(sha_function, bvh_config), split_config_(split_config), t_min_overlap_(), t_triangle_accessor_() {
  for (size_t i = 0; i < 3u; i++) {
    t_spatial_bins_[i].resize(split_config_.num_spatial_bins);
  }
}

template <typename T>
Ref<BVH<T>> SplitBVHBuilder<T>::process(const Ref<TriangleAccessor<glm::tvec3<T>>>& triangle_accessor) {
  t_triangle_accessor_ = triangle_accessor;

  // Generate references and compute root node bounding box.
  NodeSpec<T> root_spec(t_triangle_accessor_->count());

  for (uint32_t i = 0; i < t_triangle_accessor_->count(); i++) {
    Triangle<glm::tvec3<T>> tri = (*t_triangle_accessor_)[i];
    AABB<T> bounds;

    // Compute triangle bounding box.
    bounds.expand(tri[0]);
    bounds.expand(tri[1]);
    bounds.expand(tri[2]);

    t_reference_stack_.emplace_back(bounds, i);
    root_spec.bounds.expand(bounds);
  }

  t_min_overlap_ = T(root_spec.bounds.area() * split_config_.split_alpha);

  // We need cache for at most max(N - 1, num_spatial_bins) right bounds.
  t_right_bounds_.resize(std::max(root_spec.num_refs, split_config_.num_spatial_bins) - 1);

  // Clear nodes and primitive indices vectors and reserve.
  t_nodes_.clear();
  t_prim_indices_.clear();
  t_nodes_.reserve(t_right_bounds_.size());
  t_prim_indices_.reserve(t_right_bounds_.size());

  buildNode(root_spec, 0);
  return makeRef<BVH<T>>(std::move(t_nodes_), std::move(t_prim_indices_));
}

template <typename T>
uint32_t SplitBVHBuilder<T>::buildNode(const NodeSpec<T>& spec, size_t level) {
  // If we have a small enough set or we've reached max allowed depth - Create a leaf.
  if (spec.num_refs <= config_.min_leaf_size || level >= config_.max_depth) {
    return createLeaf(spec);
  }

  const float area = spec.bounds.area();
  const float leaf_sah = area * sah_function_.getPrimitiveCost(spec.num_refs);
  const float node_sah = area * sah_function_.getNodeCost(2);

  // Find best object split.
  const ObjectSplit obj_split = findObjectSplit(spec, node_sah);
  SpatialSplit<T> spatial_split;

  if (level < split_config_.max_spatial_depth) {
    // Check if there is a sufficiently large bounds overlap.
    AABB<T> overlap = obj_split.left_bounds;
    overlap.intersect(obj_split.right_bounds);

    if (overlap.area() >= t_min_overlap_) {
      spatial_split = findSpatialSplit(spec, node_sah);
    }
  }

  const float min_sah = std::min({leaf_sah, obj_split.sah, spatial_split.sah});
  // Create leaf if leaf SAH is the lowest and number of references does not exceed max leaf size.
  if (min_sah == leaf_sah && spec.num_refs <= config_.max_leaf_size) {
    return createLeaf(spec);
  }

  // Perform the split.
  std::pair<NodeSpec<T>, NodeSpec<T>> child_spec;
  if (min_sah == spatial_split.sah) {
    child_spec = performSpatialSplit(spec, spatial_split);
  }

  // If spatial split is not performed or all the references are un-split either in left or right node.
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

template <typename T>
SpatialSplit<T> SplitBVHBuilder<T>::findSpatialSplit(const NodeSpec<T>& spec, float node_sah) {
  glm::tvec3<T> origin = spec.bounds.min();
  glm::tvec3<T> bin_size = (spec.bounds.max() - origin) * (T(1.0) / static_cast<T>(split_config_.num_spatial_bins));
  glm::tvec3<T> inv_bin_size = T(1.0) / bin_size;

  // Reset spatial bins.
  for (size_t axis = 0u; axis < 3u; axis++) {
    t_spatial_bins_[axis].clear();
    t_spatial_bins_[axis].resize(split_config_.num_spatial_bins);
  }

  for (auto it = t_reference_stack_.begin() + (t_reference_stack_.size() - spec.num_refs);
       it != t_reference_stack_.end(); it++) {
    const Reference<T>& ref = *it;
    glm::tvec3<size_t> first_bin =
      glm::clamp(glm::tvec3<size_t>((ref.bounds.min() - origin) * inv_bin_size), glm::tvec3<size_t>(0u),
                 glm::tvec3<size_t>(split_config_.num_spatial_bins - 1u));
    glm::tvec3<size_t> last_bin =
      glm::clamp(glm::tvec3<size_t>((ref.bounds.max() - origin) * inv_bin_size), glm::tvec3<size_t>(0u),
                 glm::tvec3<size_t>(split_config_.num_spatial_bins - 1u));

    // Chop and bin the references.
    for (size_t axis = 0u; axis < 3u; axis++) {
      Reference<T> current_ref = ref;

      for (size_t i = first_bin[axis]; i < last_bin[axis]; i++) {
        std::pair<Reference<T>, Reference<T>> split_refs =
          splitReference(current_ref, axis, origin[axis] + bin_size[axis] * T(i + 1));
        t_spatial_bins_[axis][i].bounds.expand(split_refs.first.bounds);
        current_ref.bounds = split_refs.second.bounds;
      }

      t_spatial_bins_[axis][first_bin[axis]].enter++;
      t_spatial_bins_[axis][last_bin[axis]].exit++;
      t_spatial_bins_[axis][last_bin[axis]].bounds.expand(current_ref.bounds);
    }
  }

  // Find the best split.
  SpatialSplit<T> best_split;
  for (size_t axis = 0u; axis < 3u; axis++) {
    std::vector<SpatialBin<T>>& axis_bins = t_spatial_bins_[axis];

    // Sweep right to left and compute bounds.
    AABB<T> bounds;
    for (size_t i = split_config_.num_spatial_bins - 1; i > 0u; i--) {
      bounds.expand(axis_bins[i].bounds);
      t_right_bounds_[i - 1] = bounds;
    }

    // Sweep left to right and find the split with lowest sah.
    bounds.reset();
    size_t left_count = 0;
    size_t right_count = spec.num_refs;

    for (size_t i = 1u; i < split_config_.num_spatial_bins; i++) {
      bounds.expand(axis_bins[i - 1].bounds);
      left_count += axis_bins[i - 1].enter;
      right_count -= axis_bins[i - 1].exit;

      float sah = node_sah + bounds.area() * sah_function_.getPrimitiveCost(left_count) +
                  t_right_bounds_[i - 1].area() * sah_function_.getPrimitiveCost(right_count);
      if (sah < best_split.sah) {
        best_split.sah = sah;
        best_split.axis = axis;
        best_split.position = origin[axis] + bin_size[axis] * T(i);
      }
    }
  }

  return best_split;
}

template <typename T>
std::pair<Reference<T>, Reference<T>> SplitBVHBuilder<T>::splitReference(const Reference<T>& ref, size_t axis,
                                                                         T split_pos) const {
  Reference<T> left = ref;
  Reference<T> right = ref;

  Triangle<glm::tvec3<T>> tri = (*t_triangle_accessor_)[ref.index];

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
      glm::tvec3<T> pt = glm::mix(
        v0, v1, glm::clamp((split_pos - v0[axis]) / (v1[axis] - v0[axis]), static_cast<T>(0.0), static_cast<T>(1.0)));
      left.bounds.expand(pt);
      right.bounds.expand(pt);
    }
  }

  return {left, right};
}

template <typename T>
std::pair<NodeSpec<T>, NodeSpec<T>> SplitBVHBuilder<T>::performSpatialSplit(const NodeSpec<T>& spec,
                                                                            const SpatialSplit<T>& split) {
  std::deque<Reference<T>>& refs = t_reference_stack_;
  const size_t left_begin = refs.size() - spec.num_refs;
  size_t left_end = left_begin;
  size_t right_begin = refs.size();
  AABB<T> left_bounds;
  AABB<T> right_bounds;

  // Sort references: [left_begin, left_end][...split refs...][right_begin, right_end]
  for (size_t i = left_end; i < right_begin; i++) {
    if (refs[i].bounds.max()[split.axis] <= split.position) {
      // Bounding box is entirely on the left side.
      left_bounds.expand(refs[i].bounds);
      std::swap(refs[i], refs[left_end++]);
    } else if (refs[i].bounds.min()[split.axis] >= split.position) {
      // Bounding box is entirely on the right side.
      right_bounds.expand(refs[i].bounds);
      std::swap(refs[i--], refs[--right_begin]);
    }
  }

  // Process references that intersect with the split plane.
  while (left_end < right_begin) {
    std::pair<Reference<T>, Reference<T>> split_ref = splitReference(refs[left_end], split.axis, split.position);

    // Compute SAH for duplicate/un-split candidates.

    // Left bounds if we un-split to left.
    AABB lub = left_bounds;
    lub.expand(refs[left_end].bounds);
    // Right bounds if we un-split to right.
    AABB rub = right_bounds;
    rub.expand(refs[left_end].bounds);
    // Left bounds if we split (duplicate).
    AABB ldb = left_bounds;
    ldb.expand(split_ref.first.bounds);
    // Right bounds if we split (duplicate).
    AABB rdb = right_bounds;
    rdb.expand(split_ref.second.bounds);

    // Primitive traversal cost with and without added reference.
    float left_cost_a = sah_function_.getPrimitiveCost(left_end - left_begin);
    float right_cost_a = sah_function_.getPrimitiveCost(refs.size() - right_begin);
    float left_cost_b = sah_function_.getPrimitiveCost(left_end - left_begin + 1);
    float right_cost_b = sah_function_.getPrimitiveCost(refs.size() - right_begin + 1);

    // Compute un-split left/right cost and duplicate cost
    const float unsplit_left_sah = lub.area() * left_cost_b + right_bounds.area() * right_cost_a;
    const float unsplit_right_sah = left_bounds.area() * left_cost_a + rub.area() * right_cost_b;
    const float duplicate_sah = ldb.area() * left_cost_b + rdb.area() * right_cost_b;

    float min_sah = std::min({unsplit_left_sah, unsplit_right_sah, duplicate_sah});

    if (min_sah == unsplit_left_sah) {
      // Un-split to left.
      left_bounds = lub;
      left_end++;
    } else if (min_sah == unsplit_right_sah) {
      // Un-split to right.
      right_bounds = rub;
      std::swap(refs[left_end], refs[--right_begin]);
    } else {
      // Duplicate reference.
      left_bounds = ldb;
      right_bounds = rdb;
      refs[left_end++] = split_ref.first;
      refs.emplace_back(split_ref.second);
    }
  }

  // Produce child node specification.
  return std::make_pair(NodeSpec<T>(left_end - left_begin, left_bounds),
                        NodeSpec<T>(refs.size() - right_begin, right_bounds));
}

} // namespace bvh
} // namespace lsg

#endif // LSG_ACCELERATORS_BVH_SPLIT_BVH_BUILDER_H
