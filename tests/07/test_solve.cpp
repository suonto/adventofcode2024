#include "07/solve.h"
#include "07/equation.h"

#include <gtest/gtest.h>

#include <string>
#include <iostream>

const std::string example = R"(
190: 10 19
3267: 81 40 27
83: 17 5
156: 15 6
7290: 6 8 6 15
161011: 16 10 13
192: 17 8 14
21037: 9 7 18 13
292: 11 6 16 20
)";

TEST(Day07, Eq0)
{
    auto result = Equation(190, {10, 19}).validate();
    EXPECT_EQ(result, 1);
}

TEST(Day07, Eq1)
{
    auto result = Equation(3267, {81, 40, 27}).validate();
    EXPECT_EQ(result, 2);
}

TEST(Day07, Eq2)
{
    auto result = Equation(292, {11, 6, 16, 20}).validate();
    EXPECT_EQ(result, 1);
}

TEST(Day07, SolveA)
{
    auto result = solveA(example);
    EXPECT_EQ(result, 3749);
}

// TEST(Day07, SolveB)
// {
//     auto result = solveB(example);
//     EXPECT_EQ(result, 6);
// }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}