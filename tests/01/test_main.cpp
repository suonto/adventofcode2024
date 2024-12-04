#include <iostream>
#include "01/main.h"
#include <gtest/gtest.h>

TEST(Example, Solve) {
    auto result = solve();
    EXPECT_EQ(result, 11);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}