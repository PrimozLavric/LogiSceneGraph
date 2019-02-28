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
#include "lsg/core/Exceptions.h"

namespace lsg {

Image::Image(const std::string& name, std::vector<std::byte> data, const Format format) 
  : Identifiable(name), format_(format), format_info_(kFormatTable.at(format)), data_(std::move(data)) {
	throwIf<InitializationError>(data_.size() % format_info_.size != 0, "Image data size is not multiple of format size.");
}

Image::Image(const std::string& name, const std::byte* data, const Format format, const size_t size)
	: Identifiable(name), format_(format), format_info_(kFormatTable.at(format)), data_(data, data + size) {
	throwIf<InitializationError>(data_.size() % format_info_.size != 0, "Image data size is not multiple of format size.");
}

Image::Image(const std::string& name, const Format format, const size_t pixel_count) 
  : Identifiable(name), format_(format), format_info_(kFormatTable.at(format)), data_(pixel_count * format_info_.size, std::byte(0)) {}

Format Image::getFormat() const {
	return format_;
}

FormatInfo Image::getFormatInfo() const {
	return format_info_;
}

const std::byte* Image::rawPixelData() const {
	return data_.data();
}

void Image::copyFrom(const std::byte* input_data) {
	std::memcpy(data_.data(), input_data, data_.size());
}

}
