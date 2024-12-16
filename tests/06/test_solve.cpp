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

const std::string case0 = R"(
.....
#...#
.^.#.
)";

const std::string case1 = R"(
.....
....#
.^.#.
)";

const std::string case2 = R"(
.#...
....#
.^.#.
)";

const std::string case3 = R"(
#...
...#
^.#.
)";

const std::string caseStart = R"(
....##....
.........#
..........
..........
..........
..........
....^.....
........#.
)";

const std::string caseNoPlacementOnTraversedPath = R"(
....##....
.........#
..........
..........
........#.
..........
....^.....
..........
)";

TEST(Day06, SolveA)
{
    auto result = solveA(example);
    EXPECT_EQ(result, 41);
}

TEST(Day06, Case0)
{
    auto result = solveB(case0);
    EXPECT_EQ(result, 1);
}

TEST(Day06, Case1)
{
    auto result = solveB(case1);
    EXPECT_EQ(result, 0);
}

TEST(Day06, Case2)
{
    auto result = solveB(case2);
    EXPECT_EQ(result, 1);
}

TEST(Day06, Case3)
{
    auto result = solveB(case3);
    EXPECT_EQ(result, 0);
}

TEST(Day06, CaseStart)
{
    auto result = solveB(caseStart);
    EXPECT_EQ(result, 1);
}

TEST(Day06, CaseNoPlacementOnTraversedPath)
{
    auto result = solveB(caseNoPlacementOnTraversedPath);
    EXPECT_EQ(result, 1);
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