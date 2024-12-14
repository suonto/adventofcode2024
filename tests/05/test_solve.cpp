#include "05/solve.h"

#include <gtest/gtest.h>

#include <string>
#include <iostream>

const std::string example = R"(
47|53
97|13
97|61
97|47
75|29
61|13
75|53
29|13
97|29
53|29
61|53
97|53
61|29
47|13
75|47
97|75
47|61
75|61
47|29
75|13
53|13

75,47,61,53,29
97,61,53,29,13
75,29,13
75,97,47,61,53
61,13,29
97,13,75,29,47
)";

TEST(Day05, SolveA)
{
    auto result = solveA(example);
    EXPECT_EQ(result, 143);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}