#include <gtest/gtest.h>
#include "glm/glm.hpp"
#include "lsg/core/Identifiable.h"
#include "lsg/resources/BufferAccessor.h"

using namespace lsg;

TEST(BufferAccessor, Basic) {
  std::vector<float> data = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  Ref<Buffer> buffer = makeRef<Buffer>(data);
  BufferView view(buffer, sizeof(glm::vec3), 0u);
  BufferAccessor accessor(view, StructureType::kVec3, ComponentType::kFloat);
  TBufferAccessor<glm::vec3> typed_accessor(accessor);

  EXPECT_EQ(typed_accessor.count(), 3u);
  EXPECT_EQ(typed_accessor[0], glm::vec3(1.0f, 2.0f, 3.0f));
  EXPECT_EQ(typed_accessor[1], glm::vec3(4.0f, 5.0f, 6.0f));
  EXPECT_EQ(typed_accessor[2], glm::vec3(7.0f, 8.0f, 9.0f));
}