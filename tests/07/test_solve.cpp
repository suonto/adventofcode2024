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
    EXPECT_EQ(result, true);
}

TEST(Day07AA, Eq1)
{
    auto result = Equation(3267, {81, 40, 27}).validate();
    EXPECT_EQ(result, true);
}

TEST(Day07A, Eq2)
{
    auto result = Equation(292, {11, 6, 16, 20}).validate();
    EXPECT_EQ(result, true);
}

TEST(Day07A, Solve)
{
    auto result = solveA(example);
    EXPECT_EQ(result, 3749);
}

TEST(Day07B, Eq0)
{
    auto result = Equation(190, {10, 19}).validate_b();
    EXPECT_EQ(result, true);
}

TEST(Day07B, Eq1)
{
    auto result = Equation(3267, {81, 40, 27}).validate_b();
    EXPECT_EQ(result, true);
}

TEST(Day07B, Eq2)
{
    auto result = Equation(292, {11, 6, 16, 20}).validate_b();
    EXPECT_EQ(result, true);
}

TEST(Day07B, Eq3)
{
    auto result = Equation(156, {15, 6}).validate_b();
    EXPECT_EQ(result, true);
}

TEST(Day07B, Eq4)
{
    auto result = Equation(7290, {6, 8, 6, 15}).validate_b();
    EXPECT_EQ(result, true);
}

TEST(Day07B, Eq4sub1)
{
    auto result = Equation(486, {6, 8, 6}).validate_b();
    EXPECT_EQ(result, true);
}

TEST(Day07B, Eq4sub2)
{
    auto result = Equation(480, {6, 8}).validate_b();
    EXPECT_EQ(result, false);
}

TEST(Day07B, Eq4sub3)
{
    auto result = Equation(472, {6}).validate_b();
    EXPECT_EQ(result, false);
}

TEST(Day07B, Eq4sub4)
{
    auto result = Equation(60, {6}).validate_b();
    EXPECT_EQ(result, false);
}

TEST(Day07B, Eq5)
{
    auto result = Equation(192, {17, 8, 14}).validate_b();
    EXPECT_EQ(result, true);
}

TEST(Day07B, Eq6)
{
    auto result = Equation(225, {15, 1, 5}).validate_b();
    EXPECT_EQ(result, false);
}

TEST(Day07B, Eq7)
{
    auto result = Equation(31, {1, 5, 1, 6}).validate_b();
    EXPECT_EQ(result, false);
}

TEST(Day07B, Eq8)
{
    // 212 + 2 * 2 = 428
    auto result = Equation(428, {2, 12, 2, 2}).validate_b();
    EXPECT_EQ(result, true);
}

TEST(Day07B, Eq9)
{
    // 212 + 2 * 2 = 428
    auto result = Equation(428, {2, 12, 2, 2}).validate_b();
    EXPECT_EQ(result, true);
}

TEST(Day07B, Eq10a)
{
    // 3 * 7 || 3 || 5 * 2 != 4410
    auto result = Equation(4410, {3, 7, 3, 5, 2}).validate_b();
    EXPECT_EQ(result, false);
}

TEST(Day07B, Eq10b)
{
    // 3 * 7 || 3 || 5 * 2 = 4270
    auto result = Equation(4270, {3, 7, 3, 5, 2}).validate_b();
    EXPECT_EQ(result, true);
}

TEST(Day07B, Eq11)
{
    // 3 * 7 || 35 * 2 != 4410
    auto result = Equation(4410, {3, 7, 35, 2}).validate_b();
    EXPECT_EQ(result, false);
}

TEST(Day07B, Eq11b)
{
    // 3 * 7 || 35 + 2 != 2137
    auto result = Equation(2137, {3, 7, 35, 2}).validate_b();
    EXPECT_EQ(result, true);
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