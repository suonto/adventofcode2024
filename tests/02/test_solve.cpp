#include <gtest/gtest.h>
#include "02/report.h"
#include "02/range.h"
#include "02/solve.h"

const char *example = R"(7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9)";

TEST(Report, 0ToString)
{
    std::vector<int> row0 = {7, 6, 4, 2, 1};
    Report report0(&row0);
    EXPECT_EQ("7 6 4 2 1 ", report0.toString());
}

TEST(Report, 0IsSafe)
{
    std::vector<int> row0 = {7, 6, 4, 2, 1};
    Report report0(&row0);
    EXPECT_TRUE(report0.isSafe());
}

TEST(Report, 1IsSafe)
{
    std::vector<int> row = {1, 2, 7, 8, 9};
    Report report(&row);
    EXPECT_FALSE(report.isSafe());
}

TEST(Example2, SolveA)
{
    auto result = solveA(example);
    EXPECT_EQ(result, 2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}