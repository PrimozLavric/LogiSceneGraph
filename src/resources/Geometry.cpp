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

std::set<ComponentType> k_vertex_component_types = { ComponentType::kHalfFloat, ComponentType::kFloat, ComponentType::kDouble };
std::set<ComponentType> k_normal_component_types = { ComponentType::kHalfFloat, ComponentType::kFloat, ComponentType::kDouble };
std::set<ComponentType> k_index_component_types = { ComponentType::kUnsignedShort, ComponentType::kUnsignedInt };
std::set<ComponentType> k_uv_component_types = { ComponentType::kHalfFloat, ComponentType::kFloat, ComponentType::kDouble };


Geometry::Geometry()
	: Identifiable("Geometry") {}

void Geometry::setVertices(const BufferAccessor& vertices) {
	throwIf<InvalidArgument>(vertices.structureType() != StructureType::kVec3, "Invalid vertex structure type.");
	throwIf<InvalidArgument>(k_vertex_component_types.find(vertices.componentType()) == k_vertex_component_types.end(), "Invalid vertex structure type.");

	vertices_.emplace(vertices);
}

void Geometry::setNormals(const BufferAccessor& normals) {
	throwIf<InvalidArgument>(normals.structureType() != StructureType::kVec3, "Invalid normal structure type.");
	throwIf<InvalidArgument>(k_normal_component_types.find(normals.componentType()) == k_normal_component_types.end(), "Invalid normal structure type.");

	normals_.emplace(normals);
}

void Geometry::setIndices(const BufferAccessor& indices) {
	throwIf<InvalidArgument>(indices.structureType() != StructureType::kVec3, "Invalid index structure type.");
	throwIf<InvalidArgument>(k_index_component_types.find(indices.componentType()) == k_index_component_types.end(), "Invalid index structure type.");

	indices_.emplace(indices);
}

void Geometry::setUv(const size_t index, const BufferAccessor& uv) {
	throwIf<InvalidArgument>(uv.structureType() != StructureType::kVec2, "Invalid uv structure type.");
	throwIf<InvalidArgument>(k_uv_component_types.find(uv.componentType()) == k_uv_component_types.end(), "Invalid uv structure type.");

	uv_[index].emplace(uv);
}

const BufferAccessor& Geometry::getVertices() const {
	return vertices_.value();
}

const BufferAccessor& Geometry::getNormals() const {
	return normals_.value();
}

const BufferAccessor& Geometry::getIndices() const {
	return indices_.value();
}

const BufferAccessor& Geometry::getUv(const size_t index) const {
	return uv_[index].value();
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
