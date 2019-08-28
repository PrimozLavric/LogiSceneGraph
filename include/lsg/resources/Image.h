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

#ifndef LSG_RESOURCES_IMAGE_H
#define LSG_RESOURCES_IMAGE_H

#include <cstddef>
#include <memory>
#include <vector>
#include "lsg/core/Identifiable.h"
#include "lsg/core/Ref.h"
#include "lsg/resources/Format.h"

namespace lsg {

class Image : public Identifiable, public RefCounter<Image> {
 public:
  template <typename T>
  Image(const std::string& name, const std::vector<T>& data, Format format, size_t width, size_t height = 1u,
        size_t depth = 1u);

  template <typename T>
  Image(const std::string& name, const T* data, size_t size, Format format, size_t width, size_t height = 1u,
        size_t depth = 1u);

  Image(const std::string& name, Format format, size_t width, size_t height = 1u, size_t depth = 1u);

  size_t width() const;

  size_t height() const;

  size_t depth() const;

  inline Format getFormat() const {
    return format_;
  }

  size_t pixelSize() const;

  size_t numChannels() const;

  FormatInfo getFormatInfo() const;

  std::byte* at(size_t x, size_t y = 0u, size_t z = 0u);

  const std::byte* at(size_t x, size_t y = 0u, size_t z = 0u) const;

  const std::byte* rawPixelData() const;

  void copyFrom(const std::byte* input_data);

  void updateProperties(Format format, size_t width, size_t height, size_t depth);

  void updateProperties(size_t width, size_t height, size_t depth);

 protected:
  void validate() const;

 private:
  Format format_;
  FormatInfo format_info_;
  size_t width_;
  size_t height_;
  size_t depth_;
  std::vector<std::byte> data_;
};

template <typename T>
Image::Image(const std::string& name, const std::vector<T>& data, Format format, size_t width, size_t height,
             size_t depth)
  : Identifiable(name), format_(format), format_info_(kFormatTable.at(format)), width_(width), height_(height),
    depth_(depth), data_(reinterpret_cast<const std::byte*>(data.data()),
                         reinterpret_cast<const std::byte*>(data.data()) + (data.size() * sizeof(T))) {
  validate();
}

template <typename T>
Image::Image(const std::string& name, const T* data, size_t size, Format format, size_t width, size_t height,
             size_t depth)
  : Identifiable(name), format_(format), format_info_(kFormatTable.at(format)), width_(width), height_(height),
    depth_(depth),
    data_(reinterpret_cast<const std::byte*>(data), reinterpret_cast<const std::byte*>(data) + size * sizeof(T)) {
  validate();
}

} // namespace lsg

#endif