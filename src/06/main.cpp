#include <iostream>
#include <string>

#include "06/main.h"
#include "06/solve.h"

const std::string input = R"(
....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...
)";

int main()
{
    std::cout << "06_main solving input" << std::endl;
    auto result = solveA(input);
    return result;
}