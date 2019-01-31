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

#include "lsg/accelerators/SBVH/Builder.h"

namespace lsg {

Reference::Reference(const AABB& bounds, const size_t index)
  : bounds(bounds),
	  index(index) {}

NodeSpec::NodeSpec(const size_t num_refs) 
  : num_refs(num_refs) {}

SBVHBuilder::SBVHBuilder(const Platform& platform, const float split_alpha) 
  : platform_(platform), split_alpha_(split_alpha) {}

void SBVHBuilder::process(const std::vector<AABB>& bounding_boxes) {
	std::vector<Reference> primary_references;
	primary_references.reserve(bounding_boxes.size());


	// Generate references and compute root node bounding box.
	NodeSpec root_spec(bounding_boxes.size());

	for (size_t i = 0; i < bounding_boxes.size(); i++) {
		primary_references.emplace_back(bounding_boxes[i], i);
		root_spec.bounds.expand(bounding_boxes[i]);
	}

	// Maximum allowable overlap relative to size of rootnode
	max_overlap_ = root_spec.bounds.area() * split_alpha_;

}

}
