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

#include "lsg/resources/Image3D.h"
#include "lsg/core/Exceptions.h"

namespace lsg {

Image3D::Image3D(const std::vector<std::byte>& data, const Format format, const size_t width, const size_t height, const size_t depth)
	: Image("Image3D", data, format),
    width_(width), height_(height), depth_(depth) {
	throwIf<InitializationError>(data.size() / getFormatInfo().size != width * height * depth, "Width * height * depth is not equal to pixel count.");
}

Image3D::Image3D(const Format format, const size_t width, const size_t height, const size_t depth)
  : Image("Image3D", format, width * height * depth),
    width_(width), height_(height), depth_(depth) {}

size_t Image3D::width() const {
	return width_;
}

size_t Image3D::height() const {
	return height_;
}

size_t Image3D::depth() const {
	return depth_;
}

ImageType Image3D::getType() const {
	return ImageType::e3D;
}


}
