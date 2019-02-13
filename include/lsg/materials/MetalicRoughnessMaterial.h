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

#ifndef LSG_MATERIALS_METALIC_ROUGHNESS_MATERIAL_H
#define LSG_MATERIALS_METALIC_ROUGHNESS_MATERIAL_H

#include <glm/glm.hpp>

#include "lsg/core/Shared.h"
#include "lsg/materials/Material.h"
#include "lsg/resources/Texture.h"

namespace lsg {

class MetalicRoughnessMaterial : public Material {
public:
	MetalicRoughnessMaterial(const std::string& name = "MetalicRoughnessMaterial", glm::vec4 base_color = glm::vec4(1.0f), float metalic_factor = 1.0f, 
		                       float roughness_factor = 1.0f, float emissive_factor = 0.0f, Shared<Texture> base_color_tex = {}, Shared<Texture> metalic_roughness_tex = {},
		                       Shared<Texture> normal_tex = {}, Shared<Texture> emissive_tex = {});

  glm::vec4 baseColor() const;

  float metalicFactor() const;

  float roughnessFactor() const;

  float emissiveFactor() const;

  Ref<Texture> baseColorTex() const;

  Ref<Texture> metalicRoughnessTex() const;

  Ref<Texture> normalTex() const;

  Ref<Texture> emissiveTex() const;

  void setBaseColor(const glm::vec4& base_color);

  void setMetalicFactor(float metalic_factor);

  void setRoughnessFactor(float roughness_factor);

  void setEmissiveFactor(float emissive_factor);

  void setBaseColorTex(const Shared<Texture>& base_color_tex);

  void setMetalicRoughnessTex(const Shared<Texture>& metalic_roughness_tex);

  void setNormalTex(const Shared<Texture>& normal_tex);

  void setEmissiveTex(const Shared<Texture>& emissive_tex);

private:
	glm::vec4 base_color_;
	float metalic_factor_;
	float roughness_factor_;
	float emissive_factor_;

	Shared<Texture> base_color_tex_;
	Shared<Texture> metalic_roughness_tex_;
	Shared<Texture> normal_tex_;
	Shared<Texture> emissive_tex_;
};

}

#endif // LSG_MATERIALS_METALIC_ROUGHNESS_MATERIAL_H