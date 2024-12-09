#include <iostream>
#include "03/solve.h"
#include <gtest/gtest.h>

const char *example = R"(xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5)))";

TEST(Day03, SolveA)
{
    auto result = solveA(example);
    EXPECT_EQ(result, 161);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}