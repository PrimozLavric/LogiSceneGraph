#include <gtest/gtest.h>
#include "lsg/core/Identifiable.h"

using namespace lsg;

TEST(Identifiable, NameAndIdUniqueness) {
	Identifiable a("A");
	Identifiable b("B");

  // Basic.
	EXPECT_EQ(a.name(), "A");
	EXPECT_EQ(b.name(), "B");
	EXPECT_NE(a.id(), b.id());

  // Copy constructor test.
	Identifiable copied(a);
	EXPECT_EQ(copied.name(), a.name());
	EXPECT_NE(a.id(), copied.id());

  // Copy assignment test.
	copied = b;
  EXPECT_EQ(copied.name(), b.name());
  EXPECT_NE(b.id(), copied.id());

  // Move constructor test.
  size_t id = a.id();
  Identifiable moved(std::move(a));
  EXPECT_EQ(moved.name(), "A");
  EXPECT_EQ(moved.id(), id);

  // Move assignment test.
  id = b.id();
  moved = std::move(b);
  EXPECT_EQ(moved.name(), "B");
  EXPECT_EQ(moved.id(), id);
}