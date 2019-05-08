#include <gtest/gtest.h>
#include "lsg/accelerators/BVH/BVH.h"
#include "lsg/accelerators/BVH/BVHBuilder.h"
#include "lsg/math/AABB.h"

using namespace lsg;

void testRayIntersection(std::vector<AABB<float>> boxes, Ray<float> ray) {
  bvh::BVHBuilder<float> builder(bvh::SAHFunction("test", 0.0, 1000.0, 1u, 1u));
  Shared<BVH<float>> tree = builder.process(boxes);

  std::vector<uint32_t> indices = tree->rayIntersect(ray);
  std::set<uint32_t> indices_set(indices.begin(), indices.end());

  for (uint32_t i = 0; i < boxes.size(); i++) {
    EXPECT_EQ(ray.intersectAABB(boxes[i]), indices_set.find(i) != indices_set.end());
  }
}

TEST(BVH, RayIntersection) {
  std::vector<AABB<float>> boxes = {{{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}},
                                    {{3.0, 3.0, 3.0}, {4.0, 4.0, 4.0}},
                                    {{0.0, 2.0, 3.0}, {2.0, 3.0, 4.0}},
                                    {{0.0, 3.0, 2.0}, {1.0, 4.0, 3.0}}};

  Ray<float> ray({2.0f, 2.0f, 2.0f}, {3.5f, 3.5f, 3.5f});

  testRayIntersection(boxes, ray);
}