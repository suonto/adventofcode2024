#include <iostream>
#include "04/main.h"
#include "04/solve.h"

const char *input = R"(
MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX
)";

int main()
{
    std::cout << "04 main solving input" << std::endl;
    // auto result = solveA(input);
    auto result = solveB(input);
    return result;
}