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

#include "lsg/core/Identifiable.h"
#include "lsg/resources/Format.h"
#include <cstddef>
#include <memory>
#include <vector>

namespace lsg {

enum class ImageType { e1D, e2D, e3D };

class Image : public Identifiable, public std::enable_shared_from_this<Image> {
 public:
  Image(const std::string& name, std::vector<std::byte> data, Format format);

  Image(const std::string& name, const std::byte* data, Format format, size_t size);

  Image(const std::string& name, Format format, size_t pixel_count);

  virtual size_t width() const = 0;

  virtual size_t height() const = 0;

  virtual size_t depth() const = 0;

  virtual ImageType getType() const = 0;

  Format getFormat() const;

  FormatInfo getFormatInfo() const;

  const std::byte* rawPixelData() const;

  void copyFrom(const std::byte* input_data);

  virtual ~Image() = default;

 private:
  Format format_;
  FormatInfo format_info_;
  std::vector<std::byte> data_;
};

} // namespace lsg

#endif