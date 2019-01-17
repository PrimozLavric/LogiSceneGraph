#include <gtest/gtest.h>
#include <string>
#include "lsg/core/Object.h"
#include "lsg/components/Transform.h"

using namespace lsg;

TEST(Transform, Basic) {
	Ref<Object> a = make_ref<Object>("A");
	a->addComponent<Transform>();
	Ref<Transform> transform = a->getComponent<Transform>();

}