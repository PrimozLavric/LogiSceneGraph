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
#include "lsg/materials/Material.h"
#include "lsg/resources/Texture.h"

namespace lsg {

class MetallicRoughnessMaterial : public Material {
 public:
  /**
   * @brief Initialize MetallicRoughnessMaterial members.
   *
   * @param	name                    Name of the material. Default is: "MetalicRoughnessMaterial".
   * @param	base_color_factor       Material's base color.
   * @param	metalic_factor          Metalness of the material.
   * @param	roughness_factor        Roughness of the material.
   * @param	emissive_factor         Intensity of the light being emitted by the material.
   * @param	base_color_tex          Base color texture.
   * @param	metalic_roughness_tex   Metallic roughness texture.
   * @param	normal_tex              Normal texture.
   * @param	emissive_tex            Emissive texture.
   */
  explicit MetallicRoughnessMaterial(const std::string& name = "MetalicRoughnessMaterial",
                                     glm::vec4 base_color_factor = glm::vec4(1.0f), float metalic_factor = 1.0f,
                                     float roughness_factor = 1.0f, glm::vec3 emissive_factor = glm::vec3(0.0f),
                                     TextureUV base_color_tex = TextureUV(),
                                     TextureUV metalic_roughness_tex = TextureUV(), TextureUV normal_tex = TextureUV(),
                                     TextureUV emissive_tex = TextureUV());

  /**
   * @brief   Retrieve material's base color.
   *
   * @return	Material's base color.
   */
  glm::vec4 baseColorFactor() const;

  /**
   * @brief   Retrieve metalness of the material.
   *
   * @return	Metalness of the material.
   */
  float metallicFactor() const;

  /**
   * @brief   Retrieve roughness of the material.
   *
   * @return  Roughness of the material.
   */
  float roughnessFactor() const;

  /**
   * @brief	  Retrieve intensity of the light being emitted by the material.
   *
   * @return  Intensity of the light being emitted by the material.
   */
  glm::vec3 emissiveFactor() const;

  /**
   * @brief	  Retrieve reference to the base color texture.
   *
   * @return	Reference to the base color texture. Null reference if not set.
   */
  const Ref<Texture>& baseColorTex() const;

  /**
   * @brief	  Retrieve reference to the metallic roughness texture.
   *
   * @return	Reference to the metallic roughness texture. Null reference if not set.
   */
  const Ref<Texture>& metallicRoughnessTex() const;

  /**
   * @brief	  Retrieve reference to the normal texture.
   *
   * @return	Reference to the normal texture. Null reference if not set.
   */
  const Ref<Texture>& normalTex() const;

  /**
   * @brief	  Retrieve reference to the emissive texture.
   *
   * @return	Reference to the emissive texture. Null reference if not set.
   */
  const Ref<Texture>& emissiveTex() const;

  /**
   * @brief	Set material's base color.
   *
   * @param	base_color  Material's base color.
   */
  void setBaseColorFactor(const glm::vec4& base_color);

  /**
   * @brief	Set metalness of the material.
   *
   * @param	metalic_factor  Metalness of the material.
   */
  void setMetalicFactor(float metalic_factor);

  /**
   * @brief	Set roughness of the material.
   *
   * @param	roughness_factor  Roughness of the material.
   */
  void setRoughnessFactor(float roughness_factor);

  /**
   * @brief	Set intensity of the light being emitted by the material.
   *
   * @param	emissive_factor Intensity of the light being emitted by the material.
   */
  void setEmissiveFactor(const glm::vec3& emissive_factor);

  /**
   * @brief	Set base color texture.
   *
   * @param	base_color_tex  Base color texture.
   */
  void setBaseColorTex(const TextureUV& base_color_tex);

  /**
   * @brief	Set metallic roughness texture.
   *
   * @param	metallic_roughness_tex  Metallic roughness texture.
   */
  void setMetalicRoughnessTex(const TextureUV& metallic_roughness_tex);

  /**
   * @brief Set normal texture.
   *
   * @param	normal_tex  Normal texture.
   */
  void setNormalTex(const TextureUV& normal_tex);

  /**
   * @brief Set emissive texture.
   *
   * @param emissive_tex  Emissive texture.
   */
  void setEmissiveTex(const TextureUV& emissive_tex);

 private:
  /**
   * Material's base color.
   */
  glm::vec4 base_color_factor_;

  /**
   * Metalness of the material.
   */
  float metalic_factor_;

  /**
   * Roughness of the material.
   */
  float roughness_factor_;

  /**
   * Intensity of the light being emitted by the material.
   */
  glm::vec3 emissive_factor_;

  /**
   * Base color texture.
   */
  TextureUV base_color_tex_;

  /**
   * Metallic roughness texture.
   */
  TextureUV metallic_roughness_tex_;

  /**
   * Normal texture.
   */
  TextureUV normal_tex_;

  /**
   * Emissive texture.
   */
  TextureUV emissive_tex_;
};

} // namespace lsg

#endif // LSG_MATERIALS_METALIC_ROUGHNESS_MATERIAL_H