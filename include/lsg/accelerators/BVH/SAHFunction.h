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

#ifndef LSG_ACCELERATORS_SBVH_SAHFUNCTION_H
#define LSG_ACCELERATORS_SBVH_SAHFUNCTION_H

#include <string>
#include "lsg/core/Identifiable.h"

namespace lsg {
namespace bvh {

class SAHFunction : public Identifiable {
public:
	explicit SAHFunction(const std::string& name = "Default",
		float node_cost = 1.0f, float primitive_cost = 1.0f,
		size_t node_batch_size = 1u, size_t primitive_batch_size = 1u);

	// SAH weights
	float getSAHPrimitiveCost() const;
	float getSAHNodeCost() const;

	// SAH costs, raw and batched
	float getCost(size_t num_child_nodes, size_t num_primitives) const;
	float getPrimitiveCost(size_t n) const;
	float getNodeCost(size_t n) const;

	// batch processing (how many ops at the price of one)
	size_t getPrimitiveBatchSize() const;
	size_t getNodeBatchSize() const;

	size_t roundToPrimitiveBatchSize(size_t n) const;
	size_t roundToNodeBatchSize(size_t n) const;

private:
	/**
	 * Cost of node traversal.
	 */
	float node_cost_;

	/**
	 * Cost of primitive intersection.
	 */
	float primitive_cost_;

	/**
	 * Batch size used for rounding for node SAH computation.
	 */
	size_t node_batch_size_;

	/**
	 * Batch size used for rounding for primitive SAH computation.
	 */
	size_t primitive_batch_size_;
};

}
}

#endif  // LSG_ACCELERATORS_SBVH_SAHFUNCTION_H