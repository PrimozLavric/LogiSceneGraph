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

#include "lsg/materials/MetallicRoughnessMaterial.h"

namespace lsg {

MetallicRoughnessMaterial::MetallicRoughnessMaterial(const std::string& name, glm::vec4 base_color_factor,
                                                     float metalic_factor, float roughness_factor,
                                                     glm::vec3 emissive_factor,
                                                     float transmission_factor, float ior, TextureUV base_color_tex,
                                                     TextureUV metalic_roughness_tex, TextureUV normal_tex,
                                                     TextureUV emissive_tex, TextureUV transmission_tex)
  : Material(name), base_color_factor_(base_color_factor), metalic_factor_(metalic_factor),
    roughness_factor_(roughness_factor), emissive_factor_(emissive_factor), transmission_factor_(transmission_factor),
    ior_(ior), base_color_tex_(std::move(base_color_tex)), metallic_roughness_tex_(std::move(metalic_roughness_tex)),
    normal_tex_(std::move(normal_tex)), emissive_tex_(std::move(emissive_tex)),
    transmission_tex_(std::move(transmission_tex)) {}

glm::vec4 MetallicRoughnessMaterial::baseColorFactor() const {
  return base_color_factor_;
}

float MetallicRoughnessMaterial::metallicFactor() const {
  return metalic_factor_;
}

float MetallicRoughnessMaterial::roughnessFactor() const {
  return roughness_factor_;
}

glm::vec3 MetallicRoughnessMaterial::emissiveFactor() const {
  return emissive_factor_;
}

float MetallicRoughnessMaterial::transmissionFactor() const {
  return transmission_factor_;
}

float MetallicRoughnessMaterial::ior() const {
  return ior_;
}

const Ref<Texture>& MetallicRoughnessMaterial::baseColorTex() const {
  return base_color_tex_.texture;
}

const Ref<Texture>& MetallicRoughnessMaterial::metallicRoughnessTex() const {
  return metallic_roughness_tex_.texture;
}

const Ref<Texture>& MetallicRoughnessMaterial::normalTex() const {
  return normal_tex_.texture;
}

const Ref<Texture>& MetallicRoughnessMaterial::emissiveTex() const {
  return emissive_tex_.texture;
}

const Ref<Texture>& MetallicRoughnessMaterial::transmissionTexture() const {
  return emissive_tex_.texture;
}

void MetallicRoughnessMaterial::setBaseColorFactor(const glm::vec4& base_color) {
  base_color_factor_ = base_color;
  incrementVersion();
}

void MetallicRoughnessMaterial::setMetalicFactor(const float metalic_factor) {
  metalic_factor_ = metalic_factor;
  incrementVersion();
}

void MetallicRoughnessMaterial::setRoughnessFactor(const float roughness_factor) {
  roughness_factor_ = roughness_factor;
  incrementVersion();
}

void MetallicRoughnessMaterial::setEmissiveFactor(const glm::vec3& emissive_factor) {
  emissive_factor_ = emissive_factor;
  incrementVersion();
}

void MetallicRoughnessMaterial::setTransmissionFactor(float transmission_factor) {
  transmission_factor_ = transmission_factor;
  incrementVersion();
}

void MetallicRoughnessMaterial::setIor(float ior) {
  ior_ = ior;
  incrementVersion();
}

void MetallicRoughnessMaterial::setBaseColorTex(const TextureUV& base_color_tex) {
  base_color_tex_ = base_color_tex;
  incrementVersion();
}

void MetallicRoughnessMaterial::setMetalicRoughnessTex(const TextureUV& metallic_roughness_tex) {
  metallic_roughness_tex_ = metallic_roughness_tex;
  incrementVersion();
}

void MetallicRoughnessMaterial::setNormalTex(const TextureUV& normal_tex) {
  normal_tex_ = normal_tex;
  incrementVersion();
}

void MetallicRoughnessMaterial::setEmissiveTex(const TextureUV& emissive_tex) {
  emissive_tex_ = emissive_tex;
  incrementVersion();
}

void MetallicRoughnessMaterial::setTransmissionTex(const TextureUV& transmission_tex) {
  transmission_tex_ = transmission_tex;
  incrementVersion();
}

} // namespace lsg
