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

#ifndef LSG_RESOURCES_IMAGE2D_H
#define LSG_RESOURCES_IMAGE2D_H

#include "lsg/resources/Image.h"

namespace lsg {

class Image2D : public Image, public std::enable_shared_from_this<Image2D> {
public:
	Image2D(const std::vector<std::byte>& data, Format format, size_t width, size_t height);

	Image2D(Format format, size_t width, size_t height);

	size_t width() const override;

	size_t height() const override;

	size_t depth() const override;

	ImageType getType() const override;

private:
	size_t width_;
	size_t height_;
};

}

#endif