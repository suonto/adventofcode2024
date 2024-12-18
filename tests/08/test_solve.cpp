#include "08/solve.h"

#include <gtest/gtest.h>

#include <string>

const std::string example = R"(
............
........0...
.....0......
.......0....
....0.......
......A.....
............
............
........A...
.........A..
............
............
)";

TEST(Day08, SolveA)
{
    auto result = solveA(example);
    EXPECT_EQ(result, 14);
}

// TEST(Day08, SolveB)
// {
//     auto result = solveB(example);
//     EXPECT_EQ(result, 6);
// }

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}