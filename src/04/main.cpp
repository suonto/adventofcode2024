#include <iostream>
#include <string>

#include "04/main.h"
#include "04/solve.h"

const std::string input = R"(
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
    auto result = solveB(input);
    return result;
}