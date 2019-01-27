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


BufferAccessor::BufferAccessor(BufferView buffer_view, const size_t offset, const vk::Format format)
  : buffer_view_(std::move(buffer_view)), byte_offset_(offset), format_(format), format_info_(kFormatTable.at(format_)) {
	validate();
}

const BufferView& BufferAccessor::bufferView() const {
  return buffer_view_;
}

size_t BufferAccessor::byteOffset() const {
  return byte_offset_;
}

size_t BufferAccessor::count() const {
	return buffer_view_.count();
}

vk::Format BufferAccessor::format() const {
  return format_;
}


const FormatInfo& BufferAccessor::formatInfo() const {
  return format_info_;
}

void BufferAccessor::setByteOffset(const size_t byte_offset) {
  byte_offset_ = byte_offset;
  validate();
}

void BufferAccessor::setFormat(const vk::Format format) {
  format_ = format;
  format_info_ = kFormatTable.at(format_);
  validate();
}

void BufferAccessor::validate() const {
	throwIf<InitializationError>(byte_offset_ + format_info_.size > buffer_view_.stride(),
	                      "Bad buffer accessor (offset + element_size > BufferView.stride).");
}


}
