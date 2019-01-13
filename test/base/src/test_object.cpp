#include <gtest/gtest.h>
#include <string>
#include "lsg/core/Object.h"

using namespace lsg;

class SpecialObj : public Object {
public:
  explicit SpecialObj(const std::string& name)
    : Object(name) {}
};

TEST(Object, Hierarchy) {
	Ref<Object> a = make_ref<Object>("A");
	Ref<Object> b = make_ref<Object>("B");
	Ref<Object> c = make_ref<Object>("C");
	Ref<Object> d1 = make_ref<Object>("D");
	Ref<Object> d2 = make_ref<SpecialObj>("D");
	
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

  // Find object in hierarchy of object A.
	EXPECT_EQ(a->find("A"), a);
	EXPECT_EQ(a->find("B"), b);
	EXPECT_EQ(a->find("C"), c);

	std::cout << "______" << std::endl;
	EXPECT_EQ(a->find("D"), d1);
	std::cout << "______" << std::endl;
	EXPECT_EQ(a->find<SpecialObj>("D"), d2);
	EXPECT_EQ(a->find<SpecialObj>("C"), nullptr);
	EXPECT_EQ(a->find("DoesNotExist"), nullptr);

  // D is not a direct descendant of object A
  EXPECT_EQ(a->getChild("D"), nullptr);
}


