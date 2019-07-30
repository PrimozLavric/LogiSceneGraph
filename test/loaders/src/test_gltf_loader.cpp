#include <gtest/gtest.h>
#include "glm/glm.hpp"
#include "lsg/accelerators/BVH/SplitBVHBuilder.h"
#include "lsg/components/Mesh.h"
#include "lsg/core/Identifiable.h"
#include "lsg/loaders/GLTFLoader.h"

using namespace lsg;

TEST(GLTFLoader, Basic) {
  GLTFLoader loader;
  std::vector<Ref<Scene>> scenes = loader.load("./testdata/lantern/Lantern.gltf");

  for (const auto& scene : scenes) {
    for (const auto& root_object : scene->children()) {
      root_object->traverseDown([](const Ref<Object>& obj) {
        std::cout << obj->name() << std::endl;
        const Ref<Mesh>& mesh = obj->getComponent<Mesh>();
        if (mesh) {
          for (const auto& subMesh : mesh->subMeshes()) {
            const Ref<Geometry>& geometry = subMesh->geometry();
            const AABB<float>& aabb = geometry->getBoundingBox();
            glm::tvec3<float> min = aabb.min();
            glm::tvec3<float> max = aabb.max();
            std::cout << min.x << " " << min.y << " " << min.z << std::endl;
            std::cout << max.x << " " << max.y << " " << max.z << std::endl;
          }
        }

        return true;
      });
    }
  }
}