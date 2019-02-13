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
#include "glm/detail/type_vec3.hpp"


namespace lsg {

class Geometry : public Identifiable, public std::enable_shared_from_this<Geometry> {
public:
  Geometry();

  void setIndices(const TBufferAccessor<uint32_t>& indices);

	void setVertices(const TBufferAccessor<glm::tvec3<float>>& vertices);

	void setNormals(const TBufferAccessor<glm::tvec3<float>>& normals);

	void setTangents(const TBufferAccessor<glm::tvec4<float>>& tangents);

	void setColors(const TBufferAccessor<glm::tvec4<float>>& colors);

	void setUv(size_t index, const TBufferAccessor<glm::tvec2<float>>& uv);

	const BufferAccessor& getVertices() const;

	const BufferAccessor& getNormals() const;

	const BufferAccessor& getIndices() const;

	const BufferAccessor& getTangents() const;

	const BufferAccessor& getColors() const;

	const BufferAccessor& getUv(size_t index) const;

	void clearVertices();

	void clearNormals();

	void clearIndices();

	void clearTangents();

  void clearColors();

	void clearUv(size_t index);

	bool hasVertices() const;

	bool hasNormals() const;

	bool hasIndices() const;

	bool hasTangents() const;

	bool hasColors() const;

	bool hasUv(size_t index) const;

private:
	std::optional<TBufferAccessor<uint32_t>> indices_;
	std::optional<TBufferAccessor<glm::tvec3<float>>> vertices_;
	std::optional<TBufferAccessor<glm::tvec3<float>>> normals_;
	std::optional<TBufferAccessor<glm::tvec4<float>>> tangents_;
	std::optional<TBufferAccessor<glm::tvec4<float>>> colors_;
	std::array<std::optional<TBufferAccessor<glm::tvec2<float>>>, 8u> uv_;
};

}

#endif // LSG_RESOURCES_GEOMETRY_H
