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

#ifndef LSG_LOADERS_GLTFLOADER_H
#define LSG_LOADERS_GLTFLOADER_H

#include <tinygltf/tiny_gltf.h>
#include "lsg/core/Object.h"
#include "lsg/core/Scene.h"
#include "lsg/resources/BufferAccessor.h"
#include "lsg/resources/Image.h"
#include "lsg/resources/Texture.h"

namespace lsg {

class GLTFLoader {
 public:
  std::vector<Ref<Scene>> load(const std::string& filename);

 protected:
  tinygltf::Model loadModelASCII(const std::string& filename);

  static ComponentType parseType(int32_t type);

  static StructureType parseStructure(int32_t structure);

 protected:
  static std::vector<Ref<Object>> loadObjects(const tinygltf::Model& model);

  static BufferAccessor loadBuffer(const tinygltf::Model& model, size_t accessor_index);

  static Ref<Image> loadImage(const tinygltf::Model& model, size_t image_index);

  static std::pair<Filter, MipmapMode> parseFilterMode(int mode);

  static Wrapping parseWrapMode(int mode);

  static Ref<Sampler> loadSampler(const tinygltf::Model& model, size_t sampler_index);

  static Ref<Texture> loadTexture(const tinygltf::Model& model, size_t texture_index);

 private:
  tinygltf::TinyGLTF loader_;
};

} // namespace lsg

#endif // LSG_LOADERS_GLTFLOADER_H