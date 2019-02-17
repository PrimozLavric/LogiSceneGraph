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
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>
#include "lsg/resources/Buffer.h"
#include "lsg/components/Transform.h"
#include "lsg/components/Mesh.h"
#include "lsg/materials/MetalicRoughnessMaterial.h"

namespace lsg {

std::vector<Shared<Scene>> GLTFLoader::load(const std::string& filename) {
	tinygltf::Model model = loadModelASCII(filename);
	std::vector<Shared<Scene>> scenes;
	std::vector<Shared<Object>> objects = loadObjects(model);

  for (const auto& scene : model.scenes) {
	  std::vector<Shared<Object>> scene_objects;

    for (const auto idx : scene.nodes) {
		  scene_objects.emplace_back(objects[idx]);
    }

	  scenes.emplace_back(Shared<Scene>::create(scene.name, scene_objects));
  }

	return scenes;
}

ComponentType GLTFLoader::parseType(const int32_t type) {
  switch (type) {
    case TINYGLTF_COMPONENT_TYPE_BYTE:
		  return ComponentType::kByte;
	  case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
		  return ComponentType::kUnsignedByte;
	  case TINYGLTF_COMPONENT_TYPE_SHORT:
		  return ComponentType::kShort;
	  case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
		  return ComponentType::kUnsignedShort;
	  case TINYGLTF_COMPONENT_TYPE_INT:
		  return ComponentType::kInt;
	  case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
		  return ComponentType::kUnsignedInt;
	  case TINYGLTF_COMPONENT_TYPE_FLOAT:
		  return ComponentType::kFloat;
	  case TINYGLTF_COMPONENT_TYPE_DOUBLE:
		  return ComponentType::kDouble;
	  default:
		  throw InvalidArgument("Uknown component type.");
  }
}

StructureType GLTFLoader::parseStructure(const int32_t structure) {
	switch (structure) {
	case TINYGLTF_TYPE_SCALAR:
		return StructureType::kScalar;
	case TINYGLTF_TYPE_VEC2:
		return StructureType::kVec2;
	case TINYGLTF_TYPE_VEC3:
		return StructureType::kVec3;
	case TINYGLTF_TYPE_VEC4:
		return StructureType::kVec4;
	case TINYGLTF_TYPE_MAT2:
		return StructureType::kMat2;
	case TINYGLTF_TYPE_MAT3:
		return StructureType::kMat3;
	case TINYGLTF_TYPE_MAT4:
		return StructureType::kMat4;
	default:
		throw InvalidArgument("Uknown structure.");
	}
}


std::vector<Shared<Object>> GLTFLoader::loadObjects(const tinygltf::Model& model) {
	std::vector<Shared<Object>> objects;

	for (const auto& node : model.nodes) {
		objects.emplace_back(Shared<Object>::create(node.name));

    // Add transform component.
		Ref<Transform> transform = objects.back()->addComponent<Transform>();

		// If the node specifies matrix use it.
    if (!node.matrix.empty()) {
		  transform->setLocalMatrix(glm::mat4(glm::make_mat4x4(node.matrix.data())));
    } else {
      // Check if the rotation, translation and scale are set individualy.
      if (!node.rotation.empty()) {
		    transform->setRotation(glm::quat(glm::make_quat(node.rotation.data())));
      }
	    if (!node.translation.empty()) {
			  transform->setPosition(glm::vec3(glm::make_vec3(node.translation.data())));
	    }
	    if (!node.scale.empty()) {
			  transform->setScale(glm::vec3(glm::make_vec3(node.scale.data())));
	    }
    }

    // Add mesh if the node has one
    if (node.mesh != -1) {
		  Ref<Mesh> mesh = objects.back()->addComponent<Mesh>();
      for (const auto& primitives : model.meshes[node.mesh].primitives) {
        /**
         * GEOMETRY
         */
		    Shared<Geometry> geometry = Shared<Geometry>::create();

			  auto it = primitives.attributes.find("POSITION");
        if (it != primitives.attributes.end()) {
			    geometry->setVertices(loadPosOrNormals(model, it->second));
        }

		    it = primitives.attributes.find("NORMAL");
			  if (it != primitives.attributes.end()) {
				  geometry->setNormals(loadPosOrNormals(model, it->second));
			  }

			  it = primitives.attributes.find("TANGENT");
			  if (it != primitives.attributes.end()) {
				  geometry->setTangents(loadTangents(model, it->second));
			  }

			  it = primitives.attributes.find("TEXCOORD_0");
			  if (it != primitives.attributes.end()) {
				  geometry->setUv(0, loadUvs(model, it->second));
			  }

			  it = primitives.attributes.find("TEXCOORD_1");
			  if (it != primitives.attributes.end()) {
				  geometry->setUv(1, loadUvs(model, it->second));
			  }

			  it = primitives.attributes.find("COLOR_0");
			  if (it != primitives.attributes.end()) {
				  geometry->setColors(loadColors(model, it->second));
			  }

			  /**
	       * MATERIAL
	       */
			  Shared<MetalicRoughnessMaterial> lsg_material = Shared<MetalicRoughnessMaterial>::create();

        if (primitives.material != -1) {
			    tinygltf::Material material = model.materials[primitives.material];

          /**
           * Look for base color
           */
				  auto it = material.values.find("baseColorFactor");
          if (it == material.values.end()) {
			      lsg_material->setBaseColor(glm::make_vec4(it->second.ColorFactor().data()));
          }

		      it = material.values.find("baseColorTexture");


		      it = material.values.find("metalicFactor");
		      if (it == material.values.end()) {
			      lsg_material->setMetalicFactor(it->second.Factor());
		      }

			    it = material.values.find("roughnessFactor");
			    if (it == material.values.end()) {
				    lsg_material->setRoughnessFactor(it->second.Factor());
			    }


        
        }

			  mesh->addSubMesh(Shared<SubMesh>::create(geometry, lsg_material));
      }
    }
	}

  // Create hierarchy.
	for (size_t i = 0; i < model.nodes.size(); i++) {
    for (int child_idx : model.nodes[i].children) {
		  objects[i]->addChild(objects[child_idx]);
    }
	}

	return objects;
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


TBufferAccessor<uint32_t> GLTFLoader::loadIndices(const tinygltf::Model& model, size_t accessor_index) {
	tinygltf::Accessor accessor = model.accessors[accessor_index];
	tinygltf::BufferView view = model.bufferViews[accessor.bufferView];
	tinygltf::Buffer buffer = model.buffers[view.buffer];

  ComponentType component_type = parseType(accessor.componentType);
	StructureType structure_type = parseStructure(accessor.type);
	
  throwIf<LoaderError>(structure_type != StructureType::kScalar, "Invalid index structure type.");

  // Uninterleave buffer and convert to uint32_t type.
	std::vector<uint32_t> data(accessor.count);

  if (component_type == ComponentType::kShort) {
	  // If uint16_t perform conversion to uint32
    for (size_t i = 0u; i < accessor.count; i++) {
		  data[i] = *reinterpret_cast<uint16_t*>(buffer.data.data() + (view.byteOffset + i * view.byteStride + accessor.byteOffset));
    }

  } else if (component_type == ComponentType::kUnsignedInt) {
	  for (size_t i = 0u; i < accessor.count; i++) {
		  data[i] = *reinterpret_cast<uint32_t*>(buffer.data.data() + (view.byteOffset + i * view.byteStride + accessor.byteOffset));
	  }
  } else {
	  throw LoaderError("Invalid component type.");
  }
  
  return TBufferAccessor<uint32_t>(BufferView(Shared<Buffer>::create(buffer.name, data), sizeof(uint32_t)), structure_type, component_type);
}

TBufferAccessor<glm::tvec3<float>> GLTFLoader::loadPosOrNormals(const tinygltf::Model& model, size_t accessor_index) {
	tinygltf::Accessor accessor = model.accessors[accessor_index];
	tinygltf::BufferView view = model.bufferViews[accessor.bufferView];
	tinygltf::Buffer buffer = model.buffers[view.buffer];

	ComponentType component_type = parseType(accessor.componentType);
	StructureType structure_type = parseStructure(accessor.type);

	throwIf<LoaderError>(structure_type != StructureType::kVec3, "Invalid uvs structure type.");

	// Uninterleave buffer and convert to vec3<float> type.
	std::vector<glm::tvec3<float>> data(accessor.count);

	if (component_type == ComponentType::kFloat) {
		for (size_t i = 0u; i < accessor.count; i++) {
			data[i] = *reinterpret_cast<glm::tvec3<float>*>(buffer.data.data() + (view.byteOffset + i * view.byteStride + accessor.byteOffset));
		}
	}
	else {
		throw LoaderError("Invalid component type.");
	}

	return TBufferAccessor<glm::tvec3<float>>(BufferView(Shared<Buffer>::create(buffer.name, data), sizeof(glm::tvec3<float>)), structure_type, component_type);
}

TBufferAccessor<glm::tvec4<float>> GLTFLoader::loadTangents(const tinygltf::Model& model, size_t accessor_index) {
	tinygltf::Accessor accessor = model.accessors[accessor_index];
	tinygltf::BufferView view = model.bufferViews[accessor.bufferView];
	tinygltf::Buffer buffer = model.buffers[view.buffer];

	ComponentType component_type = parseType(accessor.componentType);
	StructureType structure_type = parseStructure(accessor.type);

	throwIf<LoaderError>(structure_type != StructureType::kVec4, "Invalid uvs structure type.");

	// Uninterleave buffer and convert to vec4<float> type.
	std::vector<glm::tvec4<float>> data(accessor.count);

	if (component_type == ComponentType::kFloat) {
		for (size_t i = 0u; i < accessor.count; i++) {
			data[i] = *reinterpret_cast<glm::tvec4<float>*>(buffer.data.data() + (view.byteOffset + i * view.byteStride + accessor.byteOffset));
		}
	}
	else {
		throw LoaderError("Invalid component type.");
	}

	return TBufferAccessor<glm::tvec4<float>>(BufferView(Shared<Buffer>::create(buffer.name, data), sizeof(glm::tvec4<float>)), structure_type, component_type);
}

TBufferAccessor<glm::tvec4<float>> GLTFLoader::loadColors(const tinygltf::Model& model, size_t accessor_index) {
	tinygltf::Accessor accessor = model.accessors[accessor_index];
	tinygltf::BufferView view = model.bufferViews[accessor.bufferView];
	tinygltf::Buffer buffer = model.buffers[view.buffer];

	ComponentType component_type = parseType(accessor.componentType);
	StructureType structure_type = parseStructure(accessor.type);

	// Un-interleave buffer and convert to vec4<float> type.
	std::vector<glm::tvec4<float>> data(accessor.count);

	if (component_type == ComponentType::kFloat) {
		if (structure_type == StructureType::kVec3) {
			for (size_t i = 0u; i < accessor.count; i++) {
				data[i] = *reinterpret_cast<glm::tvec4<float>*>(buffer.data.data() + (view.byteOffset + i * view.byteStride + accessor.byteOffset));
			}
		} else if (structure_type == StructureType::kVec4) {
			for (size_t i = 0u; i < accessor.count; i++) {
				data[i] = glm::tvec4<float>(*reinterpret_cast<glm::tvec3<float>*>(buffer.data.data() + (view.byteOffset + i * view.byteStride + accessor.byteOffset)), 1.0f);
			}
		}
	}
	else {
		throw LoaderError("Invalid component type.");
	}

	return TBufferAccessor<glm::tvec4<float>>(BufferView(Shared<Buffer>::create(buffer.name, data), sizeof(glm::tvec4<float>)), structure_type, component_type);
}

TBufferAccessor<glm::tvec2<float>> GLTFLoader::loadUvs(const tinygltf::Model& model, size_t accessor_index) {
	tinygltf::Accessor accessor = model.accessors[accessor_index];
	tinygltf::BufferView view = model.bufferViews[accessor.bufferView];
	tinygltf::Buffer buffer = model.buffers[view.buffer];

	ComponentType component_type = parseType(accessor.componentType);
	StructureType structure_type = parseStructure(accessor.type);

	throwIf<LoaderError>(structure_type != StructureType::kVec2, "Invalid uvs structure type.");

	// Uninterleave buffer and convert to vec2<float> type.
	std::vector<glm::tvec2<float>> data(accessor.count);

	if (component_type == ComponentType::kFloat) {
		for (size_t i = 0u; i < accessor.count; i++) {
			data[i] = *reinterpret_cast<glm::tvec2<float>*>(buffer.data.data() + (view.byteOffset + i * view.byteStride + accessor.byteOffset));
		}
	} else {
		throw LoaderError("Invalid component type.");
	}

	return TBufferAccessor<glm::tvec2<float>>(BufferView(Shared<Buffer>::create(buffer.name, data), sizeof(glm::tvec2<float>)), structure_type, component_type);
}


}
