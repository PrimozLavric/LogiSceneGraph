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

#ifndef LSG_ACCELERATORS_BVH_H
#define LSG_ACCELERATORS_BVH_H

#include "lsg/math/AABB.h"

namespace lsg {

struct BVHNode {
	BVHNode(const AABB& bounds, size_t index);

	AABB bounds;
	size_t index;
};

struct InternalBVHNode final : public BVHNode {
	InternalBVHNode(const AABB& bounds, size_t index, BVHNode* right = nullptr, BVHNode* left = nullptr);

	BVHNode* right;
	BVHNode* left;
};

struct LeafBVHNode final : public BVHNode {
	LeafBVHNode(const AABB& bounds, const size_t index, size_t start_idx, size_t num_primitives);

	size_t start_idx;
	size_t num_primitives;
};

}

#endif // LSG_ACCELERATORS_BVH_H