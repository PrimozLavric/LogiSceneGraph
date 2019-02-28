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
#include "lsg/materials/MetallicRoughnessMaterial.h"

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

        if (primitives.indices > 0) {
		  	  geometry->setIndices(loadBuffer(model, primitives.indices));
        }
        
			  auto it = primitives.attributes.find("POSITION");
        if (it != primitives.attributes.end()) {
			    geometry->setVertices(TBufferAccessor<glm::tvec3<float>>(loadBuffer(model, it->second)));
        }

		    it = primitives.attributes.find("NORMAL");
			  if (it != primitives.attributes.end()) {
				  geometry->setNormals(TBufferAccessor<glm::tvec3<float>>(loadBuffer(model, it->second)));
			  }

			  it = primitives.attributes.find("TANGENT");
			  if (it != primitives.attributes.end()) {
				  geometry->setTangents(TBufferAccessor<glm::tvec4<float>>(loadBuffer(model, it->second)));
			  }

			  it = primitives.attributes.find("TEXCOORD_0");
			  if (it != primitives.attributes.end()) {
				  geometry->setUv(0, loadBuffer(model, it->second));
			  }

			  it = primitives.attributes.find("TEXCOORD_1");
			  if (it != primitives.attributes.end()) {
				  geometry->setUv(1, loadBuffer(model, it->second));
			  }

			  it = primitives.attributes.find("COLOR_0");
			  if (it != primitives.attributes.end()) {
				  geometry->setColors(loadBuffer(model, it->second));
			  }

			  /**
	       * MATERIAL
	       */
			  Shared<MetallicRoughnessMaterial> lsg_material = Shared<MetallicRoughnessMaterial>::create();

        // Check if the material is specified.
        if (primitives.material != -1) {
			    tinygltf::Material gltf_material = model.materials[primitives.material];

				  lsg_material->setName(gltf_material.name);

				  if (auto it = gltf_material.values.find("baseColorFactor"); it != gltf_material.values.end()) {
			      lsg_material->setBaseColor(glm::make_vec4(it->second.ColorFactor().data()));
          } else {
					  lsg_material->setBaseColor(glm::vec4(1.0f));
          }

				  if (auto it = gltf_material.values.find("baseColorTexture"); it != gltf_material.values.end()) {
					  Shared<Texture> tex = loadTexture(model, it->second.TextureIndex());
					  lsg_material->setBaseColorTex(TextureUV(tex, (it->second.has_number_value) ? static_cast<uint32_t>(it->second.number_value) : 0u));
				  }

		      if (auto it = gltf_material.values.find("metalicFactor"); it != gltf_material.values.end()) {
			      lsg_material->setMetalicFactor(static_cast<float>(it->second.Factor()));
		      } else {
				    lsg_material->setMetalicFactor(1.0f);
		      }

			    if (auto it = gltf_material.values.find("roughnessFactor"); it != gltf_material.values.end()) {
				    lsg_material->setRoughnessFactor(static_cast<float>(it->second.Factor()));
			    } else {
					  lsg_material->setRoughnessFactor(1.0f);
			    }

				  if (auto it = gltf_material.values.find("metallicRoughnessTexture"); it != gltf_material.values.end()) {
					  Shared<Texture> tex = loadTexture(model, it->second.TextureIndex());
					  lsg_material->setMetalicRoughnessTex(TextureUV(tex, (it->second.has_number_value) ? static_cast<uint32_t>(it->second.number_value) : 0u));
				  }

          /**
           * Additional values.
           */
				  if (auto it = gltf_material.additionalValues.find("normalTexture"); it != gltf_material.additionalValues.end()) {
					  Shared<Texture> tex = loadTexture(model, it->second.TextureIndex());
					  lsg_material->setNormalTex(TextureUV(tex, (it->second.has_number_value) ? static_cast<uint32_t>(it->second.number_value) : 0u));
				  }

				  if (auto it = gltf_material.additionalValues.find("emissiveFactor"); it != gltf_material.additionalValues.end()) {
					  lsg_material->setEmissiveFactor(static_cast<float>(it->second.Factor()));
				  } else {
					  lsg_material->setEmissiveFactor(0.0f);
				  }

				  if (auto it = gltf_material.additionalValues.find("emissiveTexture"); it != gltf_material.additionalValues.end()) {
					  Shared<Texture> tex = loadTexture(model, it->second.TextureIndex());
					  lsg_material->setEmissiveTex(TextureUV(tex, (it->second.has_number_value) ? static_cast<uint32_t>(it->second.number_value) : 0u));
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

BufferAccessor GLTFLoader::loadBuffer(const tinygltf::Model& model, size_t accessor_index) {
	tinygltf::Accessor accessor = model.accessors[accessor_index];
	tinygltf::BufferView view = model.bufferViews[accessor.bufferView];
	tinygltf::Buffer buffer = model.buffers[view.buffer];

	ComponentType component_type = parseType(accessor.componentType);
	StructureType structure_type = parseStructure(accessor.type);

  // I byte stride is not specified i.e. is 0 then set the stride to entry size.
	size_t stride = (view.byteStride == 0) ? sizeOf(component_type) * sizeOf(structure_type) : view.byteStride;

	// Un-interleave the buffer.
	size_t entry_size = sizeOf(structure_type) * sizeOf(component_type);
	std::vector<std::byte> buffer_data(accessor.count * entry_size);
  for (size_t i = 0; i < accessor.count; i++) {
	  std::byte* gltf_entry = reinterpret_cast<std::byte*>(buffer.data.data()) + view.byteOffset + i * stride + accessor.byteOffset;
	  std::byte* logi_entry = buffer_data.data() + i * entry_size;
	  std::memcpy(logi_entry, gltf_entry, entry_size);
  }

	return BufferAccessor(Shared<Buffer>::create(buffer.name, buffer_data), structure_type, component_type);
}

Shared<Image2D> GLTFLoader::loadImage(const tinygltf::Model& model, size_t image_index) {
	tinygltf::Image gltf_img = model.images[image_index];
	StructureType structure_type = parseStructure(gltf_img.component);

  // Determine image format.
	Format img_format;
	switch (structure_type) {
	  case lsg::StructureType::kScalar:
		  img_format = Format::eR8Unorm;
		  break;
	  case lsg::StructureType::kVec2:
		  img_format = Format::eR8G8Unorm;
		  break;
	  case lsg::StructureType::kVec3:
		  img_format = Format::eR8G8B8Unorm;
		  break;
	  case lsg::StructureType::kVec4:
		  img_format = Format::eR8G8B8A8Unorm;
		  break;
	  default:
		  throw LoaderError("Failed to load image: " + gltf_img.name + ".");
		  break;
	}

  // TODO: Include name.
	return Shared<Image2D>::create(reinterpret_cast<std::byte*>(gltf_img.image.data()), img_format, gltf_img.width, gltf_img.height);
}


std::pair<Filter, MipmapMode> GLTFLoader::parseFilterMode(int mode) {
	switch (mode) {
	  case TINYGLTF_TEXTURE_FILTER_NEAREST:
		  case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
		  return { Filter::eNearest, MipmapMode::eNearest };
    case TINYGLTF_TEXTURE_FILTER_LINEAR:
	  case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:
	    return { Filter::eLinear, MipmapMode::eNearest };
    case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:
	    return { Filter::eNearest, MipmapMode::eLinear };
    case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR: 
		  return { Filter::eLinear, MipmapMode::eLinear };;
	  default:
		  throw LoaderError("Encountered unknown filter mode.");
	}
}

Wrapping GLTFLoader::parseWrapMode(int mode) {
	switch (mode) {
	  case TINYGLTF_TEXTURE_WRAP_REPEAT:
		  return Wrapping::eRepeat;
	  case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
		  return Wrapping::eClampToEdge;
	  case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
		  return Wrapping::eMirroredRepeat;
	  default:
		  throw LoaderError("Encountered unknown wrap mode.");
	}
}


Shared<Sampler> GLTFLoader::loadSampler(const tinygltf::Model& model, size_t sampler_index) {
	tinygltf::Sampler gltf_sampler = model.samplers[sampler_index];
	auto[min_filter, mipmap_mode] = parseFilterMode(gltf_sampler.minFilter);
	Filter mag_filter = parseFilterMode(gltf_sampler.magFilter).first;
	Wrapping wrap_u = parseWrapMode(gltf_sampler.wrapS);
	Wrapping wrap_v = parseWrapMode(gltf_sampler.wrapT);
	Wrapping wrap_w = parseWrapMode(gltf_sampler.wrapR);

	return Shared<Sampler>::create(mag_filter, min_filter, wrap_u, wrap_v, wrap_w, mipmap_mode);
}

Shared<Texture> GLTFLoader::loadTexture(const tinygltf::Model& model, size_t texture_index) {
	tinygltf::Texture gltf_tex = model.textures[texture_index];
	Shared<Image2D> image = loadImage(model, gltf_tex.source);
	Shared<Sampler> sampler = (gltf_tex.sampler < 0) ? Shared<Sampler>::create() : loadSampler(model, gltf_tex.sampler);

	return Shared<Texture>::create(image, sampler);
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
