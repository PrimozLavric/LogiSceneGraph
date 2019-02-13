#include <gtest/gtest.h>
#include "lsg/loaders/GLTFLoader.h"
#include "lsg/core/Identifiable.h"
#include "glm/glm.hpp"

using namespace lsg;

TEST(GLTFLoader, Basic) {
	GLTFLoader loader;
	loader.load("../testdata/lantern/Lantern.gltf");
}