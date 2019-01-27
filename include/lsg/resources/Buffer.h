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

#include "lsg/core/Shared.h"

namespace lsg {

/**
 * @brief 
 */
class Buffer : public std::enable_shared_from_this<Buffer> {
public:
	explicit Buffer(std::vector<std::byte> data);

  template <typename T>
  explicit Buffer(const std::vector<T>& data);

	size_t size() const;

	const std::byte* data() const;

  virtual ~Buffer() = default;

private:
	std::vector<std::byte> data_;
};

template <typename T>
Buffer::Buffer(const std::vector<T>& data) 
  : data_(reinterpret_cast<const std::byte*>(data.data()), 
	        reinterpret_cast<const std::byte*>(data.data()) + data.size() * sizeof(T)) { }

}

#endif // LSG_RESOURCES_BUFFER_H
