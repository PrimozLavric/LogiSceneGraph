#include <gtest/gtest.h>

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	//  This will extend the tests execution times. At this point we do not
	//  care about execution times
	::testing::FLAGS_gtest_death_test_style = "threadsafe";

	return RUN_ALL_TESTS();
}
