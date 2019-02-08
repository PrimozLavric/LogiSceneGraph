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

#include "lsg/accelerators/BVH/SAHFunction.h"

namespace lsg {
namespace bvh {

SAHFunction::SAHFunction(const std::string& name, const float node_cost, const float primitive_cost, const size_t node_batch_size,
                   const size_t primitive_batch_size)
  : Identifiable(name), node_cost_(node_cost), primitive_cost_(primitive_cost),
    node_batch_size_(node_batch_size), primitive_batch_size_(primitive_batch_size) { }

float SAHFunction::getSAHPrimitiveCost() const { return primitive_cost_; }

float SAHFunction::getSAHNodeCost() const { return node_cost_; }

float SAHFunction::getCost(const size_t num_child_nodes, const size_t num_primitives) const {
  return getNodeCost(num_child_nodes) + getPrimitiveCost(num_primitives);
}

float SAHFunction::getPrimitiveCost(const size_t n) const {
  return roundToPrimitiveBatchSize(n) * primitive_cost_;
}

float SAHFunction::getNodeCost(const size_t n) const {
  return roundToNodeBatchSize(n) * node_cost_;
}

size_t SAHFunction::getPrimitiveBatchSize() const {
  return primitive_batch_size_;
}

size_t SAHFunction::getNodeBatchSize() const {
  return node_batch_size_;
}

size_t SAHFunction::roundToPrimitiveBatchSize(const size_t n) const {
	return (n + primitive_batch_size_ - 1) / primitive_batch_size_;
}

size_t SAHFunction::roundToNodeBatchSize(const size_t n) const {
  return (n + node_batch_size_ - 1) / node_batch_size_;
}

}
}
