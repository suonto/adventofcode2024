#include "09/solve.h"

#include <gtest/gtest.h>

#include <string>
#include <iostream>

const std::string example = R"(
2333133121414131402
)";

TEST(Day09A, Solve)
{
    auto result = solveA(example);
    EXPECT_EQ(result, 1928);
}

TEST(Day09B, Solve)
{
    auto result = solveB(example);
    EXPECT_EQ(result, 2858);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}