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

#include "lsg/components/GeometryReference.h"

namespace lsg {

GeometryReference::GeometryReference(Ref<Object> owner, Shared<Geometry> geometry) 
  : Component("GeometryRference", owner), geometry_(std::move(geometry)) {}

const Shared<Geometry>& GeometryReference::getGeometry() const {
	return geometry_;
}

void GeometryReference::setGeometry(const Shared<Geometry>& geometry) {
	geometry_ = geometry;
}

}
