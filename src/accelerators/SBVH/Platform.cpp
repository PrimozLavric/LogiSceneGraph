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

#include "lsg/accelerators/SBVH/Platform.h"

namespace lsg {

Platform::Platform(const std::string& name, const float node_cost, const float primitive_cost, const size_t node_batch_size,
                   const size_t primitive_batch_size, const size_t min_leaf_size, const size_t max_leaf_size)
  : Identifiable(name), SAH_node_cost_(node_cost), SAH_primitive_cost_(primitive_cost),
    node_batch_size_(node_batch_size), primitive_batch_size_(primitive_batch_size),
    min_leaf_size_(min_leaf_size), max_leaf_size_(max_leaf_size) { }

float Platform::getSAHPrimitiveCost() const { return SAH_primitive_cost_; }

float Platform::getSAHNodeCost() const { return SAH_node_cost_; }

float Platform::getCost(const size_t num_child_nodes, const size_t num_primitives) const {
  return getNodeCost(num_child_nodes) + getPrimitiveCost(num_primitives);
}

float Platform::getPrimitiveCost(const size_t n) const {
  return roundToPrimitiveBatchSize(n) * SAH_primitive_cost_;
}

float Platform::getNodeCost(const size_t n) const {
  return roundToNodeBatchSize(n) * SAH_node_cost_;
}

size_t Platform::getPrimitiveBatchSize() const {
  return primitive_batch_size_;
}

size_t Platform::getNodeBatchSize() const {
  return node_batch_size_;
}

size_t Platform::roundToPrimitiveBatchSize(const size_t n) const {
	return (n + primitive_batch_size_ - 1) / primitive_batch_size_;
}

size_t Platform::roundToNodeBatchSize(const size_t n) const {
  return (n + node_batch_size_ - 1) / node_batch_size_;
}

size_t Platform::getMinLeafSize() const {
  return min_leaf_size_;
}

size_t Platform::getMaxLeafSize() const {
  return max_leaf_size_;
}

void Platform::setPrimitiveBatchSize(const size_t primitive_batch_size) {
  primitive_batch_size_ = primitive_batch_size;
}

void Platform::setNodeBatchSize(const size_t node_batch_size) { node_batch_size_ = node_batch_size; }

void Platform::setLeafPreferences(const size_t min_size, const size_t max_size) {
  min_leaf_size_ = min_size;
  max_leaf_size_ = max_size;
}


}
