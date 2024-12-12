#include <iostream>
#include "04/solve.h"
#include <gtest/gtest.h>

const char *exampleA = R"(
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

const char *exampleB = R"(
xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))
)";

TEST(Day03, SolveA)
{
    auto result = solveA(exampleA);
    EXPECT_EQ(result, 18);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}