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

#include "lsg/accelerators/BVH.h"

namespace lsg {

BVH::Node::Node(const AABB& bounds, const bool is_leaf)
  : bounds(bounds), is_leaf(is_leaf) {}

BVH::BVH(std::vector<Node> nodes, std::vector<uint32_t> prim_indices) 
  : nodes_(std::move(nodes)), prim_indices_(std::move(prim_indices)) {}

BVH::BVH(std::vector<Node>&& nodes, std::vector<uint32_t>&& prim_indices)
	: nodes_(std::move(nodes)), prim_indices_(std::move(prim_indices)) {}

const std::vector<BVH::Node>& BVH::getNodes() const {
	return nodes_;
}

const std::vector<uint32_t>& BVH::getPrimitiveIndices() const {
	return prim_indices_;
}

}
