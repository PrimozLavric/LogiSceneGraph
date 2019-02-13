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

#ifndef LSG_RESOURCES_BUFFER_H
#define LSG_RESOURCES_BUFFER_H

#include <memory>
#include <vector>
#include <cstddef>

#include "lsg/core/Identifiable.h"

namespace lsg {

/**
 * @brief Buffer is an object that holds raw data.
 */
class Buffer : public Identifiable, public std::enable_shared_from_this<Buffer> {
public:
  /**
	 * @brief Initialize buffer data.
	 *
	 * @param	data  Byte vector that will be used to initialize the buffer.
	 */
	explicit Buffer(std::vector<std::byte> data);

	/**
	 * @brief Initialize buffer data.
	 *
	 * @param name  Buffer name.
	 * @param	data  Byte vector that will be used to initialize the buffer.
	 */
	explicit Buffer(const std::string& name, std::vector<std::byte> data);

	/**
   * @brief Initialize buffer with vector of arbitrary type.
   *
   * @param	data  Vector of arbitrary type.
   */
	template <typename T>
	explicit Buffer(const std::string& name, const std::vector<T>& data);

  /**
   * @brief Initialize buffer with vector of arbitrary type.
	 *
	 * @param	data  Vector of arbitrary type.
   */
  template <typename T>
  explicit Buffer(const std::vector<T>& data);

  /**
	 * @brief   Size of the Buffer in bytes.
	 *
	 * @return	Size of the buffer.
	 */
	size_t size() const;

  /**
	 * @brief   Retrieve pointer to the beginning of the buffer data.
	 *
	 * @return  Retrieve pointer to the beginning of the buffer data.	
	 */
	const std::byte* data() const;

  /**
   * @brief May be extended.
   */
	virtual ~Buffer() = default;

private:
  /**
   * Buffer data.
   */
	std::vector<std::byte> data_;
};

template <typename T>
Buffer::Buffer(const std::string& name, const std::vector<T>& data)
	: Identifiable(name),
	data_(reinterpret_cast<const std::byte*>(data.data()),
		reinterpret_cast<const std::byte*>(data.data()) + data.size() * sizeof(T)) { }

template <typename T>
Buffer::Buffer(const std::vector<T>& data)
  : Identifiable("Buffer"), 
    data_(reinterpret_cast<const std::byte*>(data.data()), 
		      reinterpret_cast<const std::byte*>(data.data()) + data.size() * sizeof(T)) { }




}

#endif // LSG_RESOURCES_BUFFER_H
