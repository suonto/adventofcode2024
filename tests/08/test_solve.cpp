#include "08/solve.h"

#include <gtest/gtest.h>

#include <string>

const std::string example = R"(
............
........0...
.....0......
.......0....
....0.......
......A.....
............
............
........A...
.........A..
............
............
)";

TEST(Day08A, Solve)
{
    auto result = solveA(example);
    EXPECT_EQ(result, 14);
}

TEST(Day08B, Solve)
{
    auto result = solveB(example);
    EXPECT_EQ(result, 34);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}