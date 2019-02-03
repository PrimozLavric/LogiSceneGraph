#include <gtest/gtest.h>
#include "lsg/accelerators/BVH/Builder.h"

using namespace lsg;

TEST(SBVH, Basic) {
  std::vector<AABB> primitives;

  for (size_t i = 1; i <= 10; i++) {
	  primitives.emplace_back(glm::vec3(1.0f, 1.0f, 1.0f) * static_cast<float>(i - 1), glm::vec3(1.0f, 1.0f, 1.0f) * static_cast<float>(i) + glm::vec3(0.25f));
  }

	bvh::Builder builder;
	Shared<BVH> bvh = builder.process(primitives);
	
  /*
  std::deque<Ref<bvh::Node>> stack = { root };

  while (!stack.empty()) {
	  if (stack.front()->isLeaf()) {
		  auto leaf = stack.front().staticCast<bvh::LeafNode>();
		  std::cout << "Leaf " << leaf->bounds << ":" << std::endl;
		  std::cout << "\t[ ";
      for (auto idx : leaf->indices) {
		    std::cout << idx << " ";
      }
	    std::cout << "]" << std::endl;
	  } else {
		  auto inner = stack.front().staticCast<bvh::InnerNode>();
		  stack.emplace_back(inner->left);
		  stack.emplace_back(inner->right);
		  std::cout << "Inner node " << inner->bounds << ":" << std::endl;
	  }
	  stack.pop_front();
  }
  */

  std::cout << "end";
}