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

#include "lsg/resources/BufferView.h"
#include "lsg/core/Exceptions.h"

namespace lsg {

BufferView::BufferView(std::shared_ptr<Buffer> buffer, const size_t stride, const size_t offset, const size_t range)
  : buffer_(std::move(buffer)), data_(nullptr), stride_(stride), offset_(offset), range_(range) {
  // Validate buffer view.
  validate();

  // Pointer to data with offset applied.
  data_ = buffer_->data() + offset_;
}

BufferView::BufferView(std::shared_ptr<Buffer> buffer, const size_t stride, const size_t offset)
  : buffer_(std::move(buffer)), data_(nullptr), stride_(stride), offset_(offset), range_(buffer_->size() - offset) {
  // Validate buffer view.
  validate();

  // Pointer to data with offset applied.
  data_ = buffer_->data() + offset_;
}

const std::shared_ptr<Buffer>& BufferView::buffer() const {
  return buffer_;
}

std::byte* BufferView::data() const {
  return data_;
}

size_t BufferView::count() const {
  return range_ / stride_;
}

size_t BufferView::offset() const {
  return offset_;
}

size_t BufferView::stride() const {
  return stride_;
}

size_t BufferView::range() const {
  return range_;
}

void BufferView::validate() const {
  throwIf<InitializationError>(!buffer_, "Tried to initialize buffer view with null buffer.");

  throwIf<InitializationError>(offset_ + range_ > buffer_->size(), "Invalid BufferView! Out of bounds.");

  throwIf<InitializationError>(range_ % stride_ != 0u, "Invalid BufferView! Size is not multiple of stride.");
}

} // namespace lsg
