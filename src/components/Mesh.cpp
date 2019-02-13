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

#include "lsg/components/Mesh.h"

namespace lsg {

Mesh::Mesh(const Ref<Object> owner, std::vector<Shared<SubMesh>> sub_meshes) 
  : Component("Mesh", owner), sub_meshes_(std::move(sub_meshes)) {}

Mesh::Mesh(const Ref<Object> owner, const std::string& name, std::vector<Shared<SubMesh>> sub_meshes)
	: Component(name, owner), sub_meshes_(std::move(sub_meshes)) {}

size_t Mesh::subMeshCount() const {
	return sub_meshes_.size();
}

void Mesh::addSubMesh(const Shared<SubMesh>& sub_mesh) {
	sub_meshes_.emplace_back(sub_mesh);
}

const std::vector<Shared<SubMesh>>& Mesh::subMeshes() {
	return sub_meshes_;
}

}
