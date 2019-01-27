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

#include <vulkan/vulkan.hpp>

#include "lsg/resources/BufferView.h"
#include "lsg/resources/FormatTable.h"
#include "lsg/core/Exceptions.h"

namespace lsg {



class BufferAccessor {
public:
  /**
   * @brief	Creates BufferAccessor for the given buffer view with the given entry offset and format.
   * 
   * @param	buffer_view   Referenced buffer view.
   * @param	offset        Byte offset from begging of an entry.
   * @param	format        Vulkan format.
   */
  explicit BufferAccessor(BufferView buffer_view, size_t offset = 0u, vk::Format format = vk::Format::eUndefined);

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
   * @brief	  Retrieve number of entries.
   * 
   * @return	Number of entries.
   */
  size_t count() const;

  /**
   * @brief	  Retrieve currently set format.
   * 
   * @return	Currently set format.
   */
  vk::Format format() const;

  /**
   * @brief   Retrieve information about the format (size and channel count).
   * 
   * @return	Information about the format (size and channel count).
   */
  const FormatInfo& formatInfo() const;

  /**
   * @brief Set offset from the begging of an entry.
   * 
   * @param	byte_offset Offset in bytes.
   */
  void setByteOffset(size_t byte_offset);

  /**
   * @brief Set Vulkan format.
   * 
   * @param format  Vulkan format. 
   */
  void setFormat(vk::Format format);

private:
	/**
	 * @brief Validate that the format and offset are valid for the referenced buffer view.
	 */
	void validate() const;

  /**
   * Referenced buffer view.
   */
	BufferView buffer_view_;

  /**
   * Byte offset from begging of an entry.
   */
	size_t byte_offset_;

	/**
   * Vulkan format.
   */
	vk::Format format_;

  /**
   * Vulkan format info. Consists of element size and number of channels per element.
   */
	FormatInfo format_info_;
};

template <typename T>
class TypedBufferAccessor : public BufferAccessor {
public:

	/**
	 * @brief	Creates BufferAccessor for the given buffer view with the given entry offset and format.
	 *
	 * @param	buffer_view   Referenced buffer view.
	 * @param	offset        Byte offset from begging of an entry.
	 * @param	format        Vulkan format.
	 */
	explicit TypedBufferAccessor(BufferView buffer_view, size_t offset = 0u, vk::Format format = vk::Format::eUndefined);

  explicit TypedBufferAccessor(const BufferAccessor& other);

  explicit TypedBufferAccessor(BufferAccessor&& other);

  const T& operator[](const size_t index);

private:
	void validate();
};

template <typename T>
TypedBufferAccessor<T>::TypedBufferAccessor(const BufferView buffer_view, const size_t offset, const vk::Format format)
  : BufferAccessor(buffer_view, offset, format) {
	validate();
}

template <typename T>
TypedBufferAccessor<T>::TypedBufferAccessor(const BufferAccessor& other) : BufferAccessor(other) {
	validate();
}

template <typename T>
TypedBufferAccessor<T>::TypedBufferAccessor(BufferAccessor&& other) : BufferAccessor(std::move(other)) {
	validate();
}

template <typename T>
const T& TypedBufferAccessor<T>::operator[](const size_t index) {
	throwIf<OutOfRange>(index >= count(),
               "Tried to access element that is out of range.");

  return *reinterpret_cast<const T*>(bufferView().data() + bufferView().stride() * index + byteOffset());
}

template <typename T>
void TypedBufferAccessor<T>::validate() {
#if ENABLE_WARNINGS
	if (formatInfo().size == 0u || sizeof(T) % formatInfo().size != 0u)) {
	std::cout << "WARNING: Size of T (" << typeid(T).name() << " - " << sizeof(T) << "B) is not multiple of element size (" << formatInfo().size << ").";
  }
#endif

  throwIf<OutOfRange>(byteOffset() + sizeof(T) > bufferView().stride(), 
	              "TypedBufferAccessor out of bounds. Size exceeds BufferView stride.");
}

}

#endif LSG_RESOURCES_BUFFER_ACCESSOR_H