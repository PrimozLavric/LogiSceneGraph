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

#include "lsg/resources/Image2D.h"
#include "lsg/core/Exceptions.h"

namespace lsg {

Image2D::Image2D(const std::vector<std::byte>& data, const Format format, const size_t width, const size_t height)
  : Image("Image2D", data, format), width_(width), height_(height) {
	throwIf<InitializationError>(data.size() / getFormatInfo().size != width * height, "Width * height is not equal to pixel count.");
}

Image2D::Image2D(const std::byte* data, Format format, size_t width, size_t height)
  : Image("Image2D", data, format, width * height * kFormatTable.at(format).size), width_(width), height_(height) {
  
}

Image2D::Image2D(const Format format, const size_t width, const size_t height)
  : Image("Image2D", format, width * height), width_(width), height_(height) {}

size_t Image2D::width() const {
	return width_;
}

size_t Image2D::height() const {
	return height_;
}

size_t Image2D::depth() const {
	return 1u;
}

ImageType Image2D::getType() const {
	return ImageType::e2D;
}

}
