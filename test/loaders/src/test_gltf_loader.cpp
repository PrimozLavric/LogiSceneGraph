#include <gtest/gtest.h>
#include "lsg/loaders/GLTFLoader.h"
#include "lsg/core/Identifiable.h"
#include "lsg/components/Mesh.h"
#include "lsg/accelerators/BVH/SplitBVHBuilder.h"
#include "glm/glm.hpp"

using namespace lsg;

TEST(GLTFLoader, Basic) {
	GLTFLoader loader;
	std::vector<Shared<Scene>> scenes = loader.load("../testdata/sponza/Sponza.gltf");
	/*auto accessor = scenes[0]->rootObjects()[0]->getChild("LanternPole_Lantern")->getComponent<Mesh>()->subMeshes()[0]->geometry()->getTriangleAccessor<float>();

	bvh::SplitBVHBuilder<float> builder;
	Shared<BVH<float>> bvh = builder.process(accessor);*/
}