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

#ifndef LSG_RESOURCES_TEXTURE_H
#define LSG_RESOURCES_TEXTURE_H
#include "lsg/core/Shared.h"
#include "lsg/resources/Image.h"
#include "Sampler.h"

namespace lsg {

class Texture : public Identifiable, std::enable_shared_from_this<Texture> {
public:
	explicit Texture(Shared<Image> image, Shared<Sampler> sampler = {});

	Ref<Image> image() const;

	bool hasSampler() const;

	Ref<Sampler> sampler() const;

	void setImage(const Shared<Image>& image);

	void setSampler(const Shared<Sampler>& sampler);

private:
	Shared<Image> image_;
	Shared<Sampler> sampler_;
};

}

#endif