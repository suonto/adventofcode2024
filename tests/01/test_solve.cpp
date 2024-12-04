#include <iostream>
#include "01/solve.h"
#include <gtest/gtest.h>

const char *example = R"(
3   4
4   3
2   5
1   3
3   9
3   3
)";

TEST(Example, Solve1)
{
    auto result = solve1(example);
    EXPECT_EQ(result, 11);
}

TEST(Example, Solve2)
{
    auto result = solve2(example);
    EXPECT_EQ(result, 31);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}