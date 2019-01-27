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

namespace lsg {

class GLTFLoader {
public:
	Shared<Object> load(const std::string& filename);

	//Shared<Object> loadBinary();

protected:
	tinygltf::Model loadModelASCII(const std::string& filename);

private:
	tinygltf::TinyGLTF loader_;

};

}

#endif  // LSG_LOADERS_GLTFLOADER_H