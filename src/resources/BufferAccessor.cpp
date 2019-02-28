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

#include "lsg/resources/BufferAccessor.h"

namespace lsg {

size_t sizeOf(const StructureType structure_type) {
	switch (structure_type) {
	case StructureType::kScalar:
		return 1u;
	case StructureType::kVec2:
		return 2u;
	case StructureType::kVec3:
		return 3u;
	case StructureType::kVec4:
	case StructureType::kMat2:
		return 4u;
	case StructureType::kMat3:
		return 9u;
	case StructureType::kMat4:
		return 16u;
	default:
		throw InvalidArgument("Cannot compute size of kUnspecified structure type.");
	}
}

size_t sizeOf(const ComponentType component_type) {
	switch (component_type) {
	case ComponentType::kByte:
	case ComponentType::kUnsignedByte:
		return 1u;
	case ComponentType::kShort:
	case ComponentType::kUnsignedShort:
	case ComponentType::kHalfFloat:
		return 2u;
	case ComponentType::kInt:
	case ComponentType::kUnsignedInt:
	case ComponentType::kFloat:
		return 4u;
	case ComponentType::kLong:
	case ComponentType::kUnsignedLong:
	case ComponentType::kDouble:
		return 8u;
	default:
		throw InvalidArgument("Cannot compute size of kUnspecified component type.");
	}
}

BufferAccessor::BufferAccessor(BufferView buffer_view, const size_t element_size, const size_t offset)
  : buffer_view_(std::move(buffer_view)), element_size_(element_size), byte_offset_(offset), 
	  structure_type_(StructureType::kUnspecified), component_type_(ComponentType::kUnspecified) {

	throwIf<InitializationError>(byte_offset_ + element_size_ > buffer_view_.stride(),
		"Bad buffer accessor (offset + element_size > BufferView.stride).");
}

BufferAccessor::BufferAccessor(BufferView buffer_view, const StructureType structure_type, const ComponentType component_type, const size_t offset)
  : buffer_view_(std::move(buffer_view)), element_size_(sizeOf(structure_type) * sizeOf(component_type)), byte_offset_(offset),
    structure_type_(structure_type), component_type_(component_type) {

	throwIf<InitializationError>(byte_offset_ + element_size_ > buffer_view_.stride(),
		"Bad buffer accessor (offset + element_size > BufferView.stride).");
}

BufferAccessor::BufferAccessor(Shared<Buffer> buffer, const StructureType structure_type, const ComponentType component_type, const size_t buffer_offset)
	: buffer_view_(BufferView(std::move(buffer), sizeOf(structure_type) * sizeOf(component_type), buffer_offset)),
	  element_size_(sizeOf(structure_type) * sizeOf(component_type)), byte_offset_(0),
	  structure_type_(structure_type), component_type_(component_type) {
}


const BufferView& BufferAccessor::bufferView() const {
  return buffer_view_;
}

size_t BufferAccessor::byteOffset() const {
  return byte_offset_;
}

size_t BufferAccessor::elementSize() const {
	return element_size_;
}

size_t BufferAccessor::count() const {
	return buffer_view_.count();
}

StructureType BufferAccessor::structureType() const {
	return structure_type_;
}

ComponentType BufferAccessor::componentType() const {
	return component_type_;
}

}
