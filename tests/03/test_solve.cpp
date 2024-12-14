#include "03/solve.h"

#include <gtest/gtest.h>

#include <iostream>

const std::string exampleA = R"(
xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))
)";

const std::string exampleB = R"(
xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))
)";

TEST(Day03, SolveA)
{
    auto result = solveA(exampleA);
    EXPECT_EQ(result, 161);
}

TEST(Day03, SolveB)
{
    auto result = solveB(exampleB);
    EXPECT_EQ(result, 48);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}