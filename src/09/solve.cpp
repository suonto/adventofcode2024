#include "09/solve.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <optional>

size_t solve(const std::string &example, bool variant_b)
{
    std::istringstream stream(example);
    std::string line;
    size_t result = 0;

    // disk of ordered file blocks that belong to a file
    std::vector<std::optional<size_t>> disk;

    std::cout << '\n';
    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            continue;
        }

        for (size_t i = 0; i < line.size();)
        {
            size_t length = static_cast<size_t>(line[i] - '0');
            bool empty = (i + 1) % 2 == 0; // 1, 3, 5
            size_t id = i / 2;

            for (size_t l = 0; l < length; l++)
            {
                if (empty)
                {
                    disk.push_back(std::nullopt);
                    std::cout << '.';
                }
                else
                {
                    disk.push_back(id);
                    std::cout << std::to_string(id);
                }
            }
            i++;
        }
    }

    std::cout << std::endl;

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