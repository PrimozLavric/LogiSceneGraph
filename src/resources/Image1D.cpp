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

#include "lsg/resources/Image1D.h"
#include "lsg/core/Exceptions.h"

namespace lsg {

Image1D::Image1D(const std::vector<std::byte>& data, const Format format, const size_t width)
  : Image("Image1D", data, format), width_(width) {
	throwIf<InitializationError>((data.size() / getFormatInfo().size) != width, "Width is not equal to pixel count.");
}

Image1D::Image1D(const Format format, const size_t width)
  : Image("Image1D", format, width) { }

size_t Image1D::width() const {
	return width_;
}

size_t Image1D::height() const {
	return 1u;
}

size_t Image1D::depth() const {
	return 1u;
}

ImageType Image1D::getType() const {
	return ImageType::e1D;
}
}
