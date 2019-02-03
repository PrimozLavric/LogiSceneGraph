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

#ifndef LSG_ACCELERATORS_SBVH_PLATFORM_H
#define LSG_ACCELERATORS_SBVH_PLATFORM_H

#include <string>
#include "lsg/core/Identifiable.h"

namespace lsg {
namespace bvh {

class Platform : public Identifiable {
public:
	explicit Platform(const std::string& name = "Default",
		float node_cost = 1.0f, float primitive_cost = 1.0f,
		size_t node_batch_size = 1u, size_t primitive_batch_size = 1u,
		size_t min_leaf_size = 1u, size_t max_leaf_size = std::numeric_limits<size_t>::max());

	// SAH weights
	float getSAHPrimitiveCost() const;
	float getSAHNodeCost() const;

	// SAH costs, raw and batched
	float getCost(const size_t num_child_nodes, const size_t num_primitives) const;
	float getPrimitiveCost(const size_t n) const;
	float getNodeCost(const size_t n) const;

	// batch processing (how many ops at the price of one)
	size_t getPrimitiveBatchSize() const;
	size_t getNodeBatchSize() const;

	size_t roundToPrimitiveBatchSize(size_t n) const;
	size_t roundToNodeBatchSize(size_t n) const;

	size_t getMinLeafSize() const;
	size_t getMaxLeafSize() const;

	void setPrimitiveBatchSize(const size_t primitive_batch_size);
	void setNodeBatchSize(const size_t node_batch_size);

	// leaf preferences
	void setLeafPreferences(const size_t min_size, const size_t max_size);

private:
	/**
	 * Cost of node traversal.
	 */
	float SAH_node_cost_;

	/**
	 * Cost of primitive intersection.
	 */
	float SAH_primitive_cost_;

	/**
	 * Batch size used for rounding for node SAH computation.
	 */
	size_t node_batch_size_;

	/**
	 * Batch size used for rounding for primitive SAH computation.
	 */
	size_t primitive_batch_size_;

	/**
	 * Minimum number of primitives in leaf.
	 */
	size_t min_leaf_size_;

	/**
	 * Maximum number of primitives in leaf.
	 */
	size_t max_leaf_size_;
};

}
}

#endif