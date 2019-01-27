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

#include "lsg/loaders/GLTFLoader.h"
#include <iostream>

namespace lsg {

Shared<Object> GLTFLoader::load(const std::string& filename) {
	tinygltf::Model model = loadModelASCII(filename);
	return {};
}

tinygltf::Model GLTFLoader::loadModelASCII(const std::string& filename) {
	std::string error;
	std::string warning;
	tinygltf::Model model;

	const bool res = loader_.LoadASCIIFromFile(&model, &error, &warning, filename);

  // Print warning if any.
	if (!warning.empty()) {
		std::cout << "GLTFLoader Warning: " << warning << std::endl;
	}

  // Print error if any.
	if (!error.empty()) {
		std::cout << "GLTFLoader Error: " << error << std::endl;
	}

	if (!res) {
		throw std::runtime_error("GLTFLoader failed to load file " + filename);
	}

	return model;
}

}
