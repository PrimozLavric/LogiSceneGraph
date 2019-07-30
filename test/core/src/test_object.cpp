#include <gtest/gtest.h>
#include <string>
#include "lsg/core/Object.h"

using namespace lsg;

class ObjTypeA : public Object {
 public:
  explicit ObjTypeA(const std::string& name) : Object(name) {}
};

class ObjTypeB : public Object {
 public:
  explicit ObjTypeB(const std::string& name) : Object(name) {}
};

TEST(Object, BasicHierarchy) {
  auto a = makeRef<Object>("A");
  auto b = makeRef<Object>("B");
  const auto c = makeRef<Object>("C");
  auto d1 = makeRef<ObjTypeA>("D");
  const auto d2 = makeRef<ObjTypeB>("D");

  /* Hierarchy
         A
        / \
       B   C
      / \
     D   D
  */

  b->addChild(d1);
  b->addChild(d2);
  a->addChild(b);
  a->addChild(c);

  EXPECT_TRUE(a->getChild("B") == b);
  EXPECT_TRUE(a->getChild("C") == c);
  EXPECT_TRUE(b->getChild<ObjTypeA>("D") == d1);
  EXPECT_TRUE(b->getChild<ObjTypeB>("D") == d2);

  // Get parent test.
  EXPECT_FALSE(a->parent());
  EXPECT_EQ(b->parent(), a);
  EXPECT_EQ(c->parent(), a);
  EXPECT_EQ(d1->parent(), b);
  EXPECT_EQ(d2->parent(), b);

  // D is not a direct descendant of object A
  EXPECT_FALSE(a->getChild("D"));

  // Find object in hierarchy of object A.
  EXPECT_EQ(a->find("A"), a);
  EXPECT_EQ(a->find("B"), b);
  EXPECT_EQ(a->find("C"), c);

  // EXPECT_EQ(a->find<ObjTypeA>("D"), d1);
  // EXPECT_EQ(a->find<ObjTypeB>("D"), d2);

  // All objects should be active.
  EXPECT_TRUE(a->isActive());
  EXPECT_TRUE(b->isActive());
  EXPECT_TRUE(c->isActive());
  EXPECT_TRUE(d1->isActive());
  EXPECT_TRUE(d2->isActive());
  EXPECT_TRUE(d2->isActiveInHierarchy());

  // Check if is active in hierarchy works correctly.
  a->setActive(false);
  EXPECT_FALSE(a->isActive());
  EXPECT_TRUE(c->isActive());
  EXPECT_FALSE(c->isActiveInHierarchy());
  EXPECT_TRUE(d2->isActive());
  EXPECT_FALSE(d2->isActiveInHierarchy());

  // When d1 is detached only d2 should remain.
  d1->detach();
  EXPECT_EQ(a->find("D"), d2);

  // EXPECT_FALSE(a->find<ObjTypeA>("C"));
  // EXPECT_FALSE(a->find("DoesNotExist"));

  // After detaching B, D should no longer be accessible via find on A.
  b->detach();
  EXPECT_FALSE(a->find("D"));
}

TEST(Object, OnParentChangeCallbacks) {
  auto a = makeRef<Object>("A");
  auto b = makeRef<Object>("B");
  auto c = makeRef<Object>("B");

  const auto idObj = makeRef<Object>("test");
  size_t invocation_num = 0;

  // New parent should be A
  b->setOnParentChangeCallback(*idObj, [&](const Ref<Object>& new_parent) {
    EXPECT_EQ(new_parent, a);
    invocation_num++;
  });
  a->addChild(b);

  // New parent should be C
  b->setOnParentChangeCallback(*idObj, [&](const Ref<Object>& new_parent) {
    EXPECT_EQ(new_parent, c);
    invocation_num++;
  });
  c->addChild(b);

  // New parent should be C
  b->setOnParentChangeCallback(*idObj, [&](const Ref<Object>& new_parent) {
    EXPECT_EQ(new_parent, c);
    invocation_num++;
  });
  c->addChild(b);

  // New parent should be null
  b->setOnParentChangeCallback(*idObj, [&](const Ref<Object>& new_parent) {
    EXPECT_FALSE(new_parent);
    invocation_num++;
  });
  b->detach();

  b->removeOnParentChangeCallback(*idObj);
  c->addChild(b);

  EXPECT_EQ(invocation_num, 3u);
}

TEST(Object, HierarchyTraversal) {
  auto a = makeRef<Object>("A");
  auto b = makeRef<Object>("B");
  const auto c = makeRef<Object>("C");
  auto d = makeRef<Object>("D");
  const auto e = makeRef<Object>("E");

  /* Hierarchy
         A
       |
       B
      / \
     C   D
    /
   E
  */

  a->addChild(b);
  b->addChild(c);
  b->addChild(d);
  c->addChild(e);

  {
    // Inclusive traversal up.
    std::list<Ref<Object>> e_traverse_up = {e, c, b, a};
    e->traverseUp([&](const Ref<Object>& obj) {
      EXPECT_EQ(e_traverse_up.front(), obj);
      e_traverse_up.pop_front();
      return true;
    });

    // Exclusive traversal up.
    std::list<Ref<Object>> e_traverse_up_excl = {c, b, a};
    e->traverseUpExcl([&](const Ref<Object>& obj) {
      EXPECT_EQ(e_traverse_up_excl.front(), obj);
      e_traverse_up_excl.pop_front();
      return true;
    });

    // Inclusive traversal down from A.
    std::list<Ref<Object>> a_traverse_down = {a, b, c, e, d};
    a->traverseDown([&](const Ref<Object>& obj) {
      EXPECT_EQ(a_traverse_down.front(), obj);
      a_traverse_down.pop_front();
      return true;
    });

    // Inclusive traversal down from A.
    std::list<Ref<Object>> a_traverse_down_excl = {b, c, e, d};
    a->traverseDownExcl([&](const Ref<Object>& obj) {
      EXPECT_EQ(a_traverse_down_excl.front(), obj);
      a_traverse_down_excl.pop_front();
      return true;
    });
  }

  /**
   * EARLY TERMINATION
   */
  {
    // Inclusive traversal up.
    std::list<Ref<Object>> e_traverse_up = {e, c};
    e->traverseUp([&](const Ref<Object>& obj) {
      EXPECT_EQ(e_traverse_up.front(), obj);
      e_traverse_up.pop_front();
      return obj != c;
    });

    // Exclusive traversal up.
    std::list<Ref<Object>> e_traverse_up_excl = {c, b};
    e->traverseUpExcl([&](const Ref<Object>& obj) {
      EXPECT_EQ(e_traverse_up_excl.front(), obj);
      e_traverse_up_excl.pop_front();
      return obj != b;
    });

    // Inclusive traversal down from A.
    std::list<Ref<Object>> a_traverse_down = {a, b, c, d};
    a->traverseDown([&](const Ref<Object>& obj) {
      EXPECT_EQ(a_traverse_down.front(), obj);
      a_traverse_down.pop_front();
      return obj != c;
    });

    // Inclusive traversal down from A.
    std::list<Ref<Object>> a_traverse_down_excl = {b, c, d};
    a->traverseDownExcl([&](const Ref<Object>& obj) {
      EXPECT_EQ(a_traverse_down_excl.front(), obj);
      a_traverse_down_excl.pop_front();
      return obj != c;
    });
  }
}