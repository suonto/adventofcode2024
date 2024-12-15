#include "06/solve.h"

#include <gtest/gtest.h>

#include <string>
#include <iostream>

const std::string example = R"(
....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...
)";

TEST(Day06, SolveA)
{
    auto result = solveA(example);
    EXPECT_EQ(result, 41);
}

TEST(Day06, SolveB)
{
    auto result = solveB(example);
    EXPECT_EQ(result, 6);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}