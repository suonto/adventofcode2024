#include "02/report.h"
#include "02/range.h"
#include "02/solve.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <string>

const std::string example = R"(7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9)";

TEST(Day02, 0ToString)
{
    Report report0(1);
    int values[] = {7, 6, 4, 2, 1};
    for (int value : values)
    {
        report0.pushBack(value);
    }
    EXPECT_EQ("7 6 4 2 1", report0.toString());
}

TEST(Day02, 0IsSafe)
{

    Report report0(1);
    int values[] = {7, 6, 4, 2, 1};
    for (int value : values)
    {
        report0.pushBack(value);
    }
    EXPECT_TRUE(report0.isSafe());
}

TEST(Day02, 1IsSafe)
{
    Report report1(1);
    int values[] = {1, 2, 7, 8, 9};
    for (int value : values)
    {
        report1.pushBack(value);
    }
    EXPECT_FALSE(report1.isSafe());
}

TEST(Day02, RemoveILast)
{
    Report reportX(1);
    // at 2 (last) unsafe last 69 removes i 69
    int values[] = {81, 78, 76, 69};
    for (int value : values)
    {
        reportX.pushBack(value);
    }
    EXPECT_TRUE(reportX.isSafe());
}

TEST(Day02, RemoveINotLast)
{
    Report reportX(1);
    // at 2 (not last) unsafe 69 before valid 73 removes i 69
    int values[] = {78, 76, 69, 73};
    for (int value : values)
    {
        reportX.pushBack(value);
    }
    EXPECT_TRUE(reportX.isSafe());
}

TEST(Day02, RemovePrevFirst)
{
    Report reportX(1);
    // at 1 unsafe prev 85 at 0 (first) removes prev 85 at 0
    int values[] = {85, 78, 76, 74};
    for (int value : values)
    {
        std::cout << "push " << value << std::endl;
        reportX.pushBack(value);
        std::cout << "pushed " << value << std::endl;
    }
    EXPECT_TRUE(reportX.isSafe());
}

TEST(Day02, RemovePrevNotFirst)
{
    Report reportX(1);
    // unsafe prev 85 at 1 (not first) removes prev 85 at 1
    int values[] = {81, 85, 78, 76};
    for (int value : values)
    {
        reportX.pushBack(value);
    }
    EXPECT_TRUE(reportX.isSafe());
}

TEST(Day02, ExampleA)
{
    auto result = solve(example);
    EXPECT_EQ(result, 2);
}

TEST(Day02, ExampleB)
{
    auto result = solve(example, 1);
    EXPECT_EQ(result, 4);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}