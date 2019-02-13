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

#ifndef LSG_RESOURCES_SUB_MESH_H
#define LSG_RESOURCES_SUB_MESH_H

#include <memory>
#include "lsg/core/Identifiable.h"
#include "lsg/resources/Geometry.h"
#include "lsg/materials/Material.h"

namespace lsg {

class SubMesh : public Identifiable, public VersionTracker, public std::enable_shared_from_this<SubMesh> {
public:
	/**
	   * @brief Initialize sub-mesh with the given geometry and material.
	   *
	   * @param name      Sub-mesh name.
	   * @param geometry  Geometry.
	   * @param	material  Material
	   */
	explicit SubMesh(const std::string& name, Shared<Geometry> geometry, Shared<Material> material);

  /**
	 * @brief Initialize sub-mesh with the given geometry and material.	
	 * 
	 * @param geometry  Geometry.
	 * @param	material  Material
	 */
	explicit SubMesh(Shared<Geometry> geometry, Shared<Material> material);

  /**
	 * @brief Set sub-mesh material.	
	 * 
	 * @param	geometry  Geometry to be set.
	 */
	void setGeometry(const Shared<Geometry>& geometry);

  /**
	 * @brief Set sub-mesh material.
	 * 
	 * @param	material  Material to be set.
	 */
	void setMaterial(const Shared<Material>& material);

	/**
   * @brief Retrieve reference to the geometry.
   *
   * @return  Reference to sub-mesh geometry.
   */
	Ref<Geometry> geometry() const;

  /**
   * @brief Retrieve reference to the material.
   * 
   * @return  Reference to sub-mesh material.
   */
	Ref<Material> material() const;

private:
  /**
   * Sub-mesh geometry
   */
	Shared<Geometry> geometry_;

  /**
   * Sub-mesh material.
   */
	Shared<Material> material_;
};

}


#endif // LSG_RESOURCES_SUB_MESH_H