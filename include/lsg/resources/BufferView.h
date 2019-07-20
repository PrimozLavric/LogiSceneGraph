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

#ifndef LSG_RESOURCES_BUFFER_VIEW_H
#define LSG_RESOURCES_BUFFER_VIEW_H
#include "lsg/resources/Buffer.h"

namespace lsg {

class BufferView : public std::enable_shared_from_this<BufferView> {
 public:
  BufferView(std::shared_ptr<Buffer> buffer, size_t stride, size_t offset, size_t range);

  BufferView(std::shared_ptr<Buffer> buffer, size_t stride, size_t offset = 0u);

  /**
   * @brief	  Retrieve referenced buffer.
   *
   * @return	Referenced buffer.
   */
  const std::shared_ptr<Buffer>& buffer() const;

  /**
   * @brief	  Pointer to data referenced by buffer view.
   *
   * @return	Pointer to buffer view data.
   */
  const std::byte* data() const;

  /**
   * @brief   Number of entries in the buffer view.
   *
   * @return	Number of entries
   */
  size_t count() const;

  /**
   * @brief   Retrieve offset from start of the buffer in bytes.
   *
   * @return	Offset form start of the buffer in bytes.
   */
  size_t offset() const;

  /**
   * @brief	  Retrieve entry size in bytes.
   *
   * @return	Entry size in bytes.
   */
  size_t stride() const;

  /**
   * @brief	  Retrieve size of the buffer view in bytes.
   *
   * @return	Size of the buffer view in bytes.
   */
  size_t range() const;

 protected:
  void validate() const;

 private:
  /**
   * Referenced buffer.
   */
  std::shared_ptr<Buffer> buffer_;

  /**
   * Pointer to the beginning of the buffer view data.
   */
  const std::byte* data_;

  /**
   * Entry size in bytes.
   */
  size_t stride_;

  /**
   * Offset in bytes.
   */
  size_t offset_;

  /**
   * Size of the buffer view in bytes.
   */
  size_t range_;
};

/**
 * @brief   Buffer view that provides typed access to the data.
 *
 * @tparam	T Type of the data.
 */
template <typename T>
class TBufferView : public BufferView, public std::enable_shared_from_this<TBufferView<T>> {
 public:
  /**
   * @brief Used to construct typed buffer view with explicitly defined range.
   *
   * @param	buffer	Shared buffer object.
   * @param	offset	Offset from the beginning of the buffer.
   * @param	range	  Range of the buffer.
   */
  TBufferView(const std::shared_ptr<Buffer>& buffer, size_t offset, size_t range);

  /**
   * @brief Typed buffer view.
   *
   * @param	buffer	Shared buffer object.
   * @param	offset	Offset from the beginning of the buffer.
   */
  explicit TBufferView(const std::shared_ptr<Buffer>& buffer, size_t offset = 0u);

  /**
   * @brief Construct typed buffer view from regular buffer view.
   *
   * @param	buffer_view Regular buffer view.
   */
  explicit TBufferView(const BufferView& buffer_view);

  /**
   * @brief   Retrieve element on the given index.
   *
   * @param	  index Index of the element (index must be less than count())
   * @return  Reference to the element on the given index.
   */
  const T& operator[](size_t index);

  /**
   * @brief   Retrieve typed pointer to the data.
   *
   * @return	Typed pointer to the data.
   */
  const T* tData() const;
};

template <typename T>
TBufferView<T>::TBufferView(const std::shared_ptr<Buffer>& buffer, const size_t offset, const size_t range)
  : BufferView(buffer, sizeof(T), offset, range) {}

template <typename T>
TBufferView<T>::TBufferView(const std::shared_ptr<Buffer>& buffer, const size_t offset)
  : BufferView(buffer, sizeof(T), offset) {}

template <typename T>
TBufferView<T>::TBufferView(const BufferView& buffer_view)
  : BufferView(buffer_view.buffer(), sizeof(T), buffer_view.offset(), buffer_view.range()) {}

template <typename T>
const T& TBufferView<T>::operator[](const size_t index) {
  return *reinterpret_cast<T*>(data()[index * stride()]);
}

template <typename T>
const T* TBufferView<T>::tData() const {
  return reinterpret_cast<T*>(data());
}

} // namespace lsg

#endif // LSG_RESOURCES_BUFFER_VIEW_H