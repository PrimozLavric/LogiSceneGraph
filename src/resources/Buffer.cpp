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

#include "lsg/resources/Buffer.h"

namespace lsg {

Buffer::Buffer(std::vector<std::byte> data) : Identifiable("Buffer"), data_(std::move(data)) {}

Buffer::Buffer(const std::string& name, std::vector<std::byte> data) : Identifiable(name), data_(std::move(data)) {}

size_t Buffer::size() const {
  return data_.size();
}

const std::byte* Buffer::data() const {
  return data_.data();
}

std::byte* Buffer::data() {
  return data_.data();
}

} // namespace lsg
