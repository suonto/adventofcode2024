#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <04/grid.h>

size_t solve(const char *example, bool variant_b)
{
    std::istringstream stream(example);
    std::string line;
    size_t result = 0;

    Grid grid;

    std::cout << line << '\n';
    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            continue;
        }
        grid.addRow(line);
        std::cout << line << '\n';
    }
    std::cout << std::endl;

    return result;
}

size_t solveA(const char *example)
{
    return solve(example, false);
}

size_t solveB(const char *example)
{
    return solve(example, true);
}
