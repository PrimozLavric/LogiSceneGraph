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
#include "lsg/accelerators/BVH/Platform.h"
#include "lsg/core/Shared.h"
#include "lsg/accelerators/BVH.h"

namespace lsg {
namespace bvh {

struct ObjectSplit {
  /**
   * Sah cost of the split.
   */
	float SAH = std::numeric_limits<float>::max();

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
	AABB left_bounds = {};

  /**
   * Right child bounding box.
   */
  AABB right_bounds = {};
};

struct Reference final {
	Reference(const AABB& bounds, uint32_t index);

	AABB bounds;
	uint32_t index;
};

struct NodeSpec final {

  explicit NodeSpec(size_t num_refs, const AABB& bounds = {});

	size_t num_refs;
	AABB bounds;
};

struct Config {
	size_t max_depth = 64;
};


class Builder {
public:
	Builder(Platform platform = Platform(), const Config& config = Config());

	Shared<BVH> process(const std::vector<AABB>& bounding_boxes);

protected:
	static bool sortReferences(size_t axis, const Reference& ref_a, const Reference& ref_b);

	uint32_t buildNode(const NodeSpec& spec, size_t level);

	uint32_t createLeaf(const NodeSpec& spec);

	ObjectSplit findObjectSplit(const NodeSpec& spec, float node_sah);

	std::pair<NodeSpec, NodeSpec> performObjectSplit(const NodeSpec& spec, const ObjectSplit& split);

private:

	Platform platform_;
	Config config_;

	std::deque<Reference> reference_stack_;
	float max_overlap_;

  // Temporary processing variables:
	std::vector<AABB> t_right_bounds_;

	std::vector<BVH::Node> t_nodes_;
	std::vector<uint32_t> t_prim_indices_;
};

}
}

#endif // LSG_ACCELERATORS_BVH_BUILDER_H