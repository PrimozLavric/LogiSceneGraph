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

#include "lsg/resources/SubMesh.h"

namespace lsg {

SubMesh::SubMesh(const std::string& name, Shared<Geometry> geometry, Shared<Material> material)
	: Identifiable(name), geometry_(std::move(geometry)), material_(std::move(material)) {
}

SubMesh::SubMesh(Shared<Geometry> geometry, Shared<Material> material) 
  : Identifiable("Submesh"), geometry_(std::move(geometry)), material_(std::move(material)) {
}

void SubMesh::setGeometry(const Shared<Geometry>& geometry) {
	geometry_ = geometry;
	incrementVersion();
}

void SubMesh::setMaterial(const Shared<Material>& material) {
	material_ = material;
	incrementVersion();
}

Ref<Geometry> SubMesh::geometry() const {
	return geometry_;
}

Ref<Material> SubMesh::material() const {
	return material_;
}


}