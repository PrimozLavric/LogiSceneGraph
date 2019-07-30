#include <gtest/gtest.h>
#include <string>
#include "lsg/components/Transform.h"
#include "lsg/core/Object.h"

using namespace lsg;

void testVecNear(glm::vec3 actual, glm::vec3 expected, float epsilon) {
  EXPECT_TRUE((actual[0] - expected[0]) < epsilon && (actual[1] - expected[1]) < epsilon &&
              (actual[2] - expected[2]) < epsilon);
}
TEST(Transform, Basic) {
  Ref<Object> a = makeRef<Object>("A");
  a->addComponent<Transform>();
  Ref<Transform> transform = a->getComponent<Transform>();

  glm::vec3 pos(10.0f, 30.0f, 23.0f);
  glm::vec3 euler_rot(glm::pi<float>() / 2.0f, glm::pi<float>() / 3.0f, glm::pi<float>() / 4.0f);
  glm::quat rot(euler_rot);
  glm::vec3 scale(10.0f, 20.0f, 11.0f);

  transform->setPosition(pos);
  transform->setRotation(euler_rot);
  transform->setScale(scale);

  // Check if the position, rotation and scale were correctly set.
  EXPECT_EQ(transform->position(), pos);
  EXPECT_EQ(transform->rotation(), rot);
  testVecNear(transform->eulerRotation(), euler_rot, 1e-5);
  EXPECT_EQ(transform->scale(), scale);

  // Test rotations
  transform->rotateX(-glm::pi<float>() / 2.0f);
  testVecNear(transform->eulerRotation(), glm::vec3(0.0f, glm::pi<float>() / 3.0f, glm::pi<float>() / 4.0f), 1e-5);
  transform->rotateY(-glm::pi<float>() / 3.0f);
  testVecNear(transform->eulerRotation(), glm::vec3(0.0f, 0.0f, glm::pi<float>() / 4.0f), 1e-5);
  transform->rotateZ(-glm::pi<float>() / 4.0f);
  testVecNear(transform->eulerRotation(), glm::vec3(0.0f, 0.0f, 0.0f), 1e-5);

  // Test translations
  transform->translateX(5.0f);
  testVecNear(transform->position(), pos + glm::vec3(5.0f, 0.0f, 0.0f), 1e-5);
  transform->translateY(3.0f);
  testVecNear(transform->position(), pos + glm::vec3(5.0f, 3.0f, 0.0f), 1e-5);
  transform->translateZ(45.0f);
  testVecNear(transform->position(), pos + glm::vec3(5.0f, 3.0f, 45.0f), 1e-5);
}