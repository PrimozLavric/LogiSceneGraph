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

#ifndef LSG_RESOURCES_BUFFER_ACCESSOR_H
#define LSG_RESOURCES_BUFFER_ACCESSOR_H

#include "lsg/core/Exceptions.h"
#include "lsg/resources/BufferView.h"

namespace lsg {

enum class StructureType { kScalar, kVec2, kVec3, kVec4, kMat2, kMat3, kMat4, kUnspecified };

enum class ComponentType {
  kByte,
  kUnsignedByte,
  kShort,
  kUnsignedShort,
  kInt,
  kUnsignedInt,
  kLong,
  kUnsignedLong,
  kHalfFloat,
  kFloat,
  kDouble,
  kUnspecified
};

size_t sizeOf(const StructureType structure_type);

size_t sizeOf(const ComponentType component_type);

class BufferAccessor : std::enable_shared_from_this<BufferAccessor> {
 public:
  /**
   * @brief	Creates BufferAccessor for the given buffer view with the given element size and offset.
   *
   * @param	buffer_view   Referenced buffer view.
   * @param element_size  Size of the individual element.
   * @param	offset        Byte offset from beginning of an entry.
   */
  explicit BufferAccessor(BufferView buffer_view, size_t element_size, size_t offset = 0u);

  /**
   * @brief	Creates BufferAccessor for the given buffer view with the given structure and component type.
   *
   * @param	buffer_view     Referenced buffer view.
   * @param structure_type  Structure type.
   * @param component_type  Component type.
   * @param	offset          Byte offset from beginning of an entry.
   */
  explicit BufferAccessor(BufferView buffer_view, StructureType structure_type, ComponentType component_type,
                          size_t offset = 0u);

  /**
   * @brief Creates BufferAccessor directly from the buffer. Buffer view with stride = StructureType * ComponentType is
   * created in the process.
   *
   * @param	buffer          Referenced buffer.
   * @param	structure_type  Buffer entry structure type.
   * @param	component_type  Buffer entry component type.
   * @param	buffer_offset   Offset from the beginning of the buffer. Note: this is not an entry offset.
   */
  explicit BufferAccessor(Shared<Buffer> buffer, StructureType structure_type, ComponentType component_type,
                          size_t buffer_offset = 0u);

  /**
   * @brief	  Retrieve underlying buffer view.
   *
   * @return	Underlying buffer view.
   */
  const BufferView& bufferView() const;

  /**
   * @brief	  Retrieve byte offset from begging of an entry.
   *
   * @return	Byte offset from begging of an entry.
   */
  size_t byteOffset() const;

  /**
   * @brief   Retrieve size of the element.
   *
   * @return	Element size.
   */
  size_t elementSize() const;

  /**
   * @brief	  Retrieve number of entries.
   *
   * @return	Number of entries.
   */
  size_t count() const;

  /**
   * @brief   Retrieve structure type.
   *
   * @return	Structure type.
   */
  StructureType structureType() const;

  /**
   * @brief   Retrieve component type.
   *
   * @return	Retrieve component type.
   */
  ComponentType componentType() const;

  virtual ~BufferAccessor() = default;

 private:
  /**
   * Referenced buffer view.
   */
  BufferView buffer_view_;

  /**
   * Size of an element.
   */
  size_t element_size_;

  /**
   * Byte offset from begging of an entry.
   */
  size_t byte_offset_;

  /**
   * Specifies how the components of an element are structured.
   */
  StructureType structure_type_;

  /**
   * Specifies type of the component.
   */
  ComponentType component_type_;
};

template <typename T>
class TBufferAccessor : public BufferAccessor {
 public:
  /**
   * @brief	Creates Typed BufferAccessor for the given buffer view with the given offset.
   *
   * @param	buffer_view   Referenced buffer view.
   * @param	offset        Byte offset from begging of an entry.
   */
  explicit TBufferAccessor(const BufferView& buffer_view, size_t offset = 0u);

  explicit TBufferAccessor(const BufferView& buffer_view, StructureType structure_type, ComponentType component_type,
                           size_t offset = 0u);

  /**
   * @brief Copy constructor with BufferAccessor. Note: size of the BufferAccessor element must match sizeof(T).
   *
   * @param	other BufferAccessor.
   */
  explicit TBufferAccessor(const BufferAccessor& other);

  /**
   * @brief Move constructor with BufferAccessor. Note: size of the BufferAccessor element must match sizeof(T).
   *
   * @param	other BufferAccessor.
   */
  explicit TBufferAccessor(BufferAccessor&& other);

  /**
   * @brief   Access element on the given index.
   *
   * @param	  index Element index.
   * @return	Element on the given index.
   */
  const T& operator[](size_t index) const;
};

template <typename T>
TBufferAccessor<T>::TBufferAccessor(const BufferView& buffer_view, const size_t offset)
  : BufferAccessor(buffer_view, sizeof(T), offset) {}

template <typename T>
TBufferAccessor<T>::TBufferAccessor(const BufferView& buffer_view, const StructureType structure_type,
                                    const ComponentType component_type, const size_t offset)
  : BufferAccessor(buffer_view, structure_type, component_type, offset) {
  throwIf<InvalidArgument>(elementSize() != sizeof(T), "Invalid TBufferAccessor size(T) != elementSize");
}

template <typename T>
TBufferAccessor<T>::TBufferAccessor(const BufferAccessor& other) : BufferAccessor(other) {
  throwIf<InvalidArgument>(elementSize() != sizeof(T), "Invalid TBufferAccessor size(T) != elementSize");
}

template <typename T>
TBufferAccessor<T>::TBufferAccessor(BufferAccessor&& other) : BufferAccessor(std::move(other)) {
  throwIf<InvalidArgument>(elementSize() != sizeof(T), "Invalid TBufferAccessor size(T) != elementSize");
}

template <typename T>
const T& TBufferAccessor<T>::operator[](const size_t index) const {
  throwIf<OutOfRange>(index >= count(), "Tried to access element that is out of range.");
  return reinterpret_cast<const T&>(bufferView().data()[bufferView().stride() * index + byteOffset()]);
}

} // namespace lsg

#endif