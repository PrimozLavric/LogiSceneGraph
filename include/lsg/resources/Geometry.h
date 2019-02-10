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

#ifndef LSG_RESOURCES_GEOMETRY_H
#define LSG_RESOURCES_GEOMETRY_H

#include <array>

#include "lsg/core/Shared.h"
#include "lsg/resources/BufferAccessor.h"
#include <optional>
#include <set>


namespace lsg {

class Geometry : public Identifiable, public std::enable_shared_from_this<Geometry> {
public:
  Geometry();

	void setVertices(const BufferAccessor& vertices);

	void setNormals(const BufferAccessor& normals);

	void setIndices(const BufferAccessor& indices);

	void setUv(size_t index, const BufferAccessor& uv);

	const BufferAccessor& getVertices() const;

	const BufferAccessor& getNormals() const;

	const BufferAccessor& getIndices() const;

	const BufferAccessor& getUv(size_t index) const;

	void clearVertices();

	void clearNormals();

	void clearIndices();

	void clearUv(size_t index);

	bool hasVertices() const;

	bool hasNormals() const;

	bool hasIndices() const;

	bool hasUv(size_t index) const;

	static std::set<ComponentType> k_vertex_component_types;
	static std::set<ComponentType> k_normal_component_types;
	static std::set<ComponentType> k_index_component_types;
	static std::set<ComponentType> k_uv_component_types;
private:
	std::optional<BufferAccessor> vertices_;
	std::optional<BufferAccessor> normals_;
	std::optional<BufferAccessor> indices_;
	std::array<std::optional<BufferAccessor>, 8u> uv_;
};

}

#endif // LSG_RESOURCES_GEOMETRY_H
