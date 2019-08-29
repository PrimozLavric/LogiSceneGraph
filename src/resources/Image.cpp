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

#include "lsg/resources/Image.h"
#include <cstring>
#include "lsg/core/Exceptions.h"

namespace lsg {

Image::Image(const std::string& name, Format format, size_t width, size_t height, size_t depth)
  : Identifiable(name), format_(format), format_info_(kFormatTable.at(format)), width_(width), height_(height),
    depth_(depth), data_(format_info_.size * width_ * height_ * depth_, std::byte(0u)) {}

size_t Image::width() const {
  return width_;
}

size_t Image::height() const {
  return height_;
}

size_t Image::depth() const {
  return depth_;
}

size_t Image::pixelSize() const {
  return format_info_.size;
}
size_t Image::numChannels() const {
  return format_info_.channel_count;
}

FormatInfo Image::getFormatInfo() const {
  return format_info_;
}

std::byte* Image::at(size_t x, size_t y, size_t z) {
  return const_cast<std::byte*>(static_cast<const Image*>(this)->at(x, y, z));
}

const std::byte* Image::at(size_t x, size_t y, size_t z) const {
  const size_t pixel_size = pixelSize();
  const size_t bX = pixel_size * x;
  const size_t bY = pixel_size * y;
  const size_t bZ = pixel_size * z;

  return &data_[bX + width_ * (bY + depth_ * bZ)];
}

const std::byte* Image::rawPixelData() const {
  return data_.data();
}

void Image::copyFrom(const std::byte* input_data) {
  std::memcpy(data_.data(), input_data, data_.size());
}

void Image::updateProperties(Format format, size_t width, size_t height, size_t depth) {
  format_ = format;
  format_info_ = kFormatTable.at(format);
  width_ = width;
  height_ = height;
  depth_ = depth;
  validate();
}

void Image::updateProperties(size_t width, size_t height, size_t depth) {
  width_ = width;
  height_ = height;
  depth_ = depth;
  validate();
}

void Image::validate() const {
  throwIf<InitializationError>(data_.size() != (format_info_.size) * width_ * height_ * depth_,
                               util::strCat("Image dimensions [", width_, ", ", height_, ", ", depth_,
                                            "] are not compatible with buffer size [", data_.size(),
                                            "] and format of size [", format_info_.size, "]."));
}

} // namespace lsg
