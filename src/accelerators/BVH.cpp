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

#include <lsg/accelerators/BVH.h>

namespace lsg {

BVHNode::BVHNode(const AABB& bounds, const size_t index) 
  : bounds(bounds), index(index){}

InternalBVHNode::InternalBVHNode(const AABB& bounds, const size_t index, BVHNode* right, BVHNode* left) 
  : BVHNode(bounds, index), right(right), left(left) {}

LeafBVHNode::LeafBVHNode(const AABB& bounds, const size_t index, const size_t start_idx, const size_t num_primitives)
	: BVHNode(bounds, index), start_idx(start_idx), num_primitives(num_primitives) {}

}
