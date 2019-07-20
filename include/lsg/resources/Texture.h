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

#include "Sampler.h"
#include "lsg/resources/Image.h"

namespace lsg {

class Texture : public Identifiable, std::enable_shared_from_this<Texture> {
 public:
  explicit Texture(std::shared_ptr<Image> image, std::shared_ptr<Sampler> sampler = {});

  const std::shared_ptr<Image>& image() const;

  bool hasSampler() const;

  const std::shared_ptr<Sampler>& sampler() const;

  void setImage(const std::shared_ptr<Image>& image);

  void setSampler(const std::shared_ptr<Sampler>& sampler);

 private:
  std::shared_ptr<Image> image_;
  std::shared_ptr<Sampler> sampler_;
};

} // namespace lsg

#endif