/**
 * Project LogiSceneGraph source code
 * Copyright(C) 2019 Primoz Lavric
 *
 * This program is free software : you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.If not, see < http://www.gnu.org/licenses/>.
 */

#include "lsg/resources/Texture.h"
#include "lsg/core/Exceptions.h"

namespace lsg {

Texture::Texture(Shared<Image> image, Shared<Sampler> sampler)
  : Identifiable("Texture"), image_(std::move(image)), sampler_(std::move(sampler)) {
	throwIf<InvalidArgument>(!image_, "Tried to initialize Texture with null image.");
}

Ref<Image> Texture::image() const {
	return image_;
}

bool Texture::hasSampler() const {
	return sampler_;
}

Ref<Sampler> Texture::sampler() const {
	return sampler_;
}

void Texture::setImage(const Shared<Image>& image) {
	throwIf<InvalidArgument>(!image, "Tried to set Texture image to null.");
	image_ = image;
}

void Texture::setSampler(const Shared<Sampler>& sampler) {
	sampler_ = sampler;
}

}