#include "01/solve.h"
#include <gtest/gtest.h>

#include <iostream>
#include <string>

const std::string example = R"(
3   4
4   3
2   5
1   3
3   9
3   3
)";

TEST(Day01, SolveA)
{
    auto result = solve1(example);
    EXPECT_EQ(result, 11);
}

TEST(Day01, SolveB)
{
    auto result = solve2(example);
    EXPECT_EQ(result, 31);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}