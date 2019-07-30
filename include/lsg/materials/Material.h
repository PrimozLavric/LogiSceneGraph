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

#ifndef LSG_MATERIALS_MATERIAL_H
#define LSG_MATERIALS_MATERIAL_H

#include "lsg/core/Identifiable.h"
#include "lsg/core/Ref.h"
#include "lsg/core/VersionTracker.h"
#include "lsg/resources/Texture.h"

namespace lsg {

static constexpr uint32_t k_uv_index_unspecified = std::numeric_limits<uint32_t>::max();

/**
 * @brief Base class for all materials.
 */
class Material : public Identifiable, public RefCounter<Material>, public VersionTracker {
 public:
  /**
   * Uses the same constructor as identifiable.
   */
  using Identifiable::Identifiable;
};

/**
 * @brief Combines texture and UV coordinates index.
 */
struct TextureUV {
  /**
   * @brief Initialize members.
   *
   * @param	texture   Texture.
   * @param	uv_index  Uv coordinates index.
   */
  explicit TextureUV(Ref<Texture> texture = {}, uint32_t uv_index = k_uv_index_unspecified);

  /**
   * Texture.
   */
  Ref<Texture> texture;

  /**
   * Index of UV coordinates (references geometry).
   */
  uint32_t uv_index;
};

} // namespace lsg

#endif
