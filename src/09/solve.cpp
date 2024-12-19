#include "09/solve.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <optional>
#include <unordered_map>

void orderA(std::vector<std::optional<size_t>> &disk)
{
    size_t first = 0;
    size_t last = disk.size() - 1;

    while (true)
    {
        while (!disk[last].has_value())
        {
            last--;
        }

        while (disk[first].has_value())
        {
            first++;
        }

        if (first >= last)
        {
            break;
        }

        disk[first] = disk[last];
        disk[last] = std::nullopt;
    }
}

void orderB(std::vector<std::optional<size_t>> &disk)
{
    // First possible index map for all block sizes
    std::unordered_map<size_t, size_t> firsts = {
        {1, 0},
        {2, 0},
        {3, 0},
        {4, 0},
        {5, 0},
        {6, 0},
        {7, 0},
        {8, 0},
        {9, 0}};

    size_t last = disk.size() - 1;

    while (firsts[1] < last)
    {
        while (!disk[last].has_value())
        {
            last--;
        }
        size_t id = disk[last].value();

        // block size
        size_t size = 1;
        std::string block = std::to_string(id);

        while (disk[last - 1].has_value() && disk[last - 1].value() == id)
        {
            last--;
            size++;
            block += std::to_string(id);
        }

        std::cout << "attempting to move " << block << " at " << last << '\n';

        // find a suitable index for the block of current size
        size_t free = 0;
        // free index
        size_t free_i = 0;
        while (free < size && firsts[size] < disk.size() && firsts[size] < last)
        {
            if (disk[firsts[size]].has_value())
            {
                free = 0;
            }
            else
            {
                free++;
            }
            firsts[size]++;
        }

        if (free == size)
        {
            // move block
            std::cout << "moving block " << block << " from " << last << " to " << firsts[size] - size << '\n';
            for (size_t i = 0; i < size; i++)
            {
                free_i = firsts[size] - size + i;
                disk[free_i] = disk[last + i];
                disk[last + i] = std::nullopt;
            }

            std::cout << '\n';
        }
        else
        {
            last--;
        }
    }
}

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

    std::cout << '\n';

    if (!variant_b)
    {
        orderA(disk);
    }
    else
    {
        orderB(disk);
    }

    for (size_t i = 0; i < disk.size(); i++)
    {
        if (!disk[i].has_value())
        {
            std::cout << '.';
        }
        else
        {
            result += disk[i].value() * i;
            std::cout << std::to_string(disk[i].value());
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