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

TEST(Day07A, Eq0)
{
    auto result = Equation(190, {10, 19}).validate();
    EXPECT_EQ(result, 1);
}

TEST(Day07AA, Eq1)
{
    auto result = Equation(3267, {81, 40, 27}).validate();
    EXPECT_EQ(result, 2);
}

TEST(Day07A, Eq2)
{
    auto result = Equation(292, {11, 6, 16, 20}).validate();
    EXPECT_EQ(result, 1);
}

TEST(Day07A, Solve)
{
    auto result = solveA(example);
    EXPECT_EQ(result, 3749);
}

TEST(Day07B, Eq0)
{
    auto result = Equation(190, {10, 19}).validate_b();
    EXPECT_EQ(result, 1);
}

TEST(Day07B, Eq1)
{
    auto result = Equation(3267, {81, 40, 27}).validate_b();
    EXPECT_EQ(result, 2);
}

TEST(Day07B, Eq2)
{
    auto result = Equation(292, {11, 6, 16, 20}).validate_b();
    EXPECT_EQ(result, 1);
}

TEST(Day07B, Eq3)
{
    auto result = Equation(156, {15, 6}).validate_b();
    EXPECT_EQ(result, 1);
}

TEST(Day07B, Eq4)
{
    auto result = Equation(7290, {6, 8, 6, 15}).validate_b();
    EXPECT_EQ(result, 1);
}

TEST(Day07B, Eq4sub1)
{
    auto result = Equation(486, {6, 8, 6}).validate_b();
    EXPECT_EQ(result, 1);
}

TEST(Day07B, Eq5)
{
    auto result = Equation(192, {17, 8, 14}).validate_b();
    EXPECT_EQ(result, 1);
}

TEST(Day07B, Eq6)
{
    auto result = Equation(109137611815, {9, 4, 9, 1, 9, 5, 13, 97, 18, 1, 4}).validate_b();
    EXPECT_EQ(result, 1);
}

TEST(Day07B, Solve)
{
    auto result = solveB(example);
    EXPECT_EQ(result, 11387);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}