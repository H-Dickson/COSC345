#include <iostream>
#include <gtest/gtest.h>
using namespace std;

// Demonstrate some basic assertions.
TEST( TestName, Subtest_1) {
	ASSERT_TRUE(1 == 1);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}