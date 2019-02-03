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

#ifndef LSG_ACCELERATORS_SBVH_BUILDER_H
#define LSG_ACCELERATORS_SBVH_BUILDER_H

#include "lsg/math/AABB.h"
#include <vector>
#include <lsg/accelerators/SBVH/Platform.h>

namespace lsg {

	struct Reference final {
		Reference(const AABB& bounds, size_t index);

		AABB bounds;
		size_t index;
	};

	struct NodeSpec final {

		NodeSpec(const size_t num_refs);

		AABB bounds;
		size_t num_refs;
	};


	class SBVHBuilder {
	public:
		SBVHBuilder(const Platform& platform, float split_alpha);

		void process(const std::vector<AABB>& bounding_boxes);


	private:

		Platform platform_;

		/**
     * Spatial split area threshold, see Nvidia paper on SBVH by Martin Stich, usually 0.05.
     */
		float split_alpha_;


		std::vector<Reference> primary_references_;




		float max_overlap_;
	};


}

#endif // LSG_ACCELERATORS_SBVH_BUILDER_H
