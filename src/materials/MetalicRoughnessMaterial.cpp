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

#include "lsg/materials/MetalicRoughnessMaterial.h"

namespace lsg {

MetalicRoughnessMaterial::MetalicRoughnessMaterial(const std::string& name, glm::vec4 base_color, float metalic_factor, float roughness_factor, 
	                                                 float emissive_factor, Shared<Texture> base_color_tex, Shared<Texture> metalic_roughness_tex, 
	                                                 Shared<Texture> normal_tex, Shared<Texture> emissive_tex)
	: Material(name), base_color_(base_color), metalic_factor_(metalic_factor), roughness_factor_(roughness_factor), emissive_factor_(emissive_factor),
    base_color_tex_(base_color_tex), metalic_roughness_tex_(metalic_roughness_tex), normal_tex_(normal_tex), emissive_tex_(emissive_tex) {}

glm::vec4 MetalicRoughnessMaterial::baseColor() const {
  return base_color_;
}

float MetalicRoughnessMaterial::metalicFactor() const {
  return metalic_factor_;
}

float MetalicRoughnessMaterial::roughnessFactor() const { return 
  roughness_factor_; }

float MetalicRoughnessMaterial::emissiveFactor() const { return 
  emissive_factor_; }

Ref<Texture> MetalicRoughnessMaterial::baseColorTex() const {
  return base_color_tex_;
}

Ref<Texture> MetalicRoughnessMaterial::metalicRoughnessTex() const {
  return metalic_roughness_tex_;
}

Ref<Texture> MetalicRoughnessMaterial::normalTex() const {
  return normal_tex_;
}


Ref<Texture> MetalicRoughnessMaterial::emissiveTex() const {
  return emissive_tex_;
}

void MetalicRoughnessMaterial::setBaseColor(const glm::vec4& base_color) {
  base_color_ = base_color;
  incrementVersion();
}

void MetalicRoughnessMaterial::setMetalicFactor(const float metalic_factor) {
  metalic_factor_ = metalic_factor;
  incrementVersion();
}

void MetalicRoughnessMaterial::setRoughnessFactor(const float roughness_factor) {
  roughness_factor_ = roughness_factor;
  incrementVersion();
}

void MetalicRoughnessMaterial::setEmissiveFactor(const float emissive_factor) {
  emissive_factor_ = emissive_factor;
  incrementVersion();
}

void MetalicRoughnessMaterial::setBaseColorTex(const Shared<Texture>& base_color_tex) {
  base_color_tex_ = base_color_tex;
  incrementVersion();
}

void MetalicRoughnessMaterial::setMetalicRoughnessTex(const Shared<Texture>& metalic_roughness_tex) {
  metalic_roughness_tex_ = metalic_roughness_tex;
  incrementVersion();
}

void MetalicRoughnessMaterial::setNormalTex(const Shared<Texture>& normal_tex) {
  normal_tex_ = normal_tex;
  incrementVersion();
}

void MetalicRoughnessMaterial::setEmissiveTex(const Shared<Texture>& emissive_tex) {
  emissive_tex_ = emissive_tex;
  incrementVersion();
}

}
