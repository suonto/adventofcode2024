#include "04/solve.h"

#include <gtest/gtest.h>

#include <string>
#include <iostream>

const std::string example = R"(
MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX
)";

TEST(Day04, SolveA)
{
    auto result = solveA(example);
    EXPECT_EQ(result, 18);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}