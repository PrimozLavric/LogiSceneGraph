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
#include "lsg/core/Shared.h"
#include "lsg/core/Object.h"
#include "lsg/core/Scene.h"
#include "lsg/resources/BufferAccessor.h"
#include <glm/detail/type_vec3.hpp>

namespace lsg {

class GLTFLoader {
public:
	std::vector<Shared<Scene>> load(const std::string& filename);


protected:
	tinygltf::Model loadModelASCII(const std::string& filename);

	static ComponentType parseType(int32_t type);

	static StructureType parseStructure(int32_t structure);


protected:
	static std::vector<Shared<Object>> loadObjects(const tinygltf::Model& model);

	static TBufferAccessor<uint32_t> loadIndices(const tinygltf::Model& model, size_t accessor_index);

	static TBufferAccessor<glm::tvec3<float>> loadPosOrNormals(const tinygltf::Model& model, size_t accessor_index);

	static TBufferAccessor<glm::tvec4<float>> loadTangents(const tinygltf::Model& model, size_t accessor_index);

	static TBufferAccessor<glm::tvec4<float>> loadColors(const tinygltf::Model& model, size_t accessor_index);

	static TBufferAccessor<glm::tvec2<float>> loadUvs(const tinygltf::Model& model, size_t accessor_index);


private:
	tinygltf::TinyGLTF loader_;

};


}

#endif  // LSG_LOADERS_GLTFLOADER_H