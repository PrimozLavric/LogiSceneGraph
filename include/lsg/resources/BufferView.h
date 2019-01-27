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
#include "lsg/core/Shared.h"
#include "lsg/resources/Buffer.h"

namespace lsg {

class BufferView {
public:
  BufferView(Shared<Buffer> buffer, size_t offset, size_t stride, size_t range);

  BufferView(Shared<Buffer> buffer, size_t offset, size_t stride);

  /**
     * @brief	  Retrieve referenced buffer.
     *
     * @return	Referenced buffer.
     */
  const Shared<Buffer>& buffer() const;

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
  Shared<Buffer> buffer_;

  /**
   * Buffer view data.
   */
  const std::byte* data_;

  /**
   * Offset in bytes.
   */
  size_t offset_;

  /**
   * Entry size in bytes.
   */
  size_t stride_;

  /**
   * Size of the buffer view in bytes.
   */
  size_t range_;
};

}

#endif  // LSG_RESOURCES_BUFFER_VIEW_H