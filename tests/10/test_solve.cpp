#include "10/solve.h"

#include <gtest/gtest.h>

#include <string>

const std::string example = R"(
89010123
78121874
87430965
96549874
45678903
32019012
01329801
10456732
)";

TEST(Day10A, Solve)
{
    auto result = solveA(example);
    EXPECT_EQ(result, 36);
}

TEST(Day10B, Solve)
{
    auto result = solveB(example);
    EXPECT_EQ(result, 81);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}