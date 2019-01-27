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

#include "lsg/resources/Geometry.h"

namespace lsg {

Geometry::Geometry() : Identifiable("Geometry") {}

void Geometry::setVertices(const BufferAccessor& vertices) {
	vertices_.emplace(vertices);

  // Validate
  throwIf<InvalidArgument>(vertices_->formatInfo().channel_count == 3,
	                  "Tried to assign BufferAccessor with ", vertices_->formatInfo().channel_count, " channels (3 required).");
}

void Geometry::setNormals(const BufferAccessor& normals) {
	normals_.emplace(normals);

	// Validate
	throwIf<InvalidArgument>(normals_->formatInfo().channel_count == 3,
		                "Tried to assign BufferAccessor with ", normals_->formatInfo().channel_count, " channels (3 required).");
}

void Geometry::setIndices(const BufferAccessor& indices) {
	indices_.emplace(indices);

	throwIf<InvalidArgument>(indices_->formatInfo().channel_count == 1,
		"Tried to assign BufferAccessor with ", indices_->formatInfo().channel_count, " channels (1 required).");

	throwIf<InvalidArgument>(indices_->format() != vk::Format::eR16Uint && indices_->format() != vk::Format::eR32Uint,
		"Tried to assign BufferAccessor with invalid format (uint16 or uint32 required).");
}

void Geometry::setUv(const size_t index, const BufferAccessor& uv) {
	uv_[index].emplace(uv);

	// Validate
	throwIf<InvalidArgument>(uv_[index]->formatInfo().channel_count == 2,
		"Tried to assign BufferAccessor with ", uv_[index]->formatInfo().channel_count, " channels (2 required).");
}


void Geometry::clearVertices() {
	vertices_.reset();
}

void Geometry::clearNormals() {
	normals_.reset();
}

void Geometry::clearIndices() {
	indices_.reset();
}

void Geometry::clearUv(const size_t index) {
	uv_[index].reset();
}

bool Geometry::hasVertices() const {
	return vertices_.has_value();
}

bool Geometry::hasNormals() const {
	return normals_.has_value();
}

bool Geometry::hasIndices() const {
	return indices_.has_value();
}

bool Geometry::hasUv(const size_t index) const {
	return uv_[index].has_value();
}


}
