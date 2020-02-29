#include <iostream>
#include "gtest/gtest.h"

int ireturntwo() {
	return 2;
}

TEST(ireturntwo, returning_two) {
	EXPECT_EQ (2, ireturntwo());
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}