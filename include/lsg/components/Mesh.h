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

#ifndef LSG_COMPONENTS_MESH_H
#define LSG_COMPONENTS_MESH_H

#include "lsg/core/Component.h"
#include "lsg/core/VersionTracker.h"
#include "lsg/resources/SubMesh.h"

namespace lsg {

class Mesh : public Component, public VersionTracker, std::enable_shared_from_this<Mesh> {
 public:
  explicit Mesh(std::weak_ptr<Object> owner, std::vector<std::shared_ptr<SubMesh>> sub_meshes = {});

  explicit Mesh(std::weak_ptr<Object> owner, const std::string& name,
                std::vector<std::shared_ptr<SubMesh>> sub_meshes = {});

  size_t subMeshCount() const;

  void addSubMesh(const std::shared_ptr<SubMesh>& sub_mesh);

  const std::vector<std::shared_ptr<SubMesh>>& subMeshes();

 private:
  std::vector<std::shared_ptr<SubMesh>> sub_meshes_;
};

} // namespace lsg

#endif // LSG_COMPONENTS_GEOMETRY_REFERENCE_H
