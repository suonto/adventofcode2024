#include "grid.h"
#include "pos.h"
#include "08/solve.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <optional>
#include <unordered_set>

size_t solve(const std::string &example, bool variant_b)
{
    std::istringstream stream(example);
    std::string line;
    size_t result = 0;

    Grid<char> grid;

    std::cout << '\n';
    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            continue;
        };
    }

    std::cout << "Result " << result << std::endl;

    return result;
}

size_t solveA(const std::string &example)
{
    return solve(example, false);
}

size_t solveB(const std::string &example)
{
    return solve(example, true);
}
