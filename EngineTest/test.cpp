#include <gtest/gtest.h>

TEST(TestBasic, TestOneEqOne) {
    int i = 1;
    int j = 1;
    int k = 2;
	EXPECT_EQ(i+j, 2);
	EXPECT_TRUE(i == j);
}

int main(int argc, char** args) {

    testing::InitGoogleTest();
    RUN_ALL_TESTS();
    return 0;
}