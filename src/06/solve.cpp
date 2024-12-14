#include "grid.h"
#include "pos.h"
#include "directions.h"
#include "06/solve.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <optional>

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
        std::vector<char> row;
        for (char c : line)
        {
            row.push_back(c);
        }

        grid.addRow(row);
        std::cout << line << '\n';
    }

    std::cout << '\n'
              << "Trying grid cells" << '\n';

    GridPos guard_pos(0, 0);
    CardinalDirection guard_dir = CardinalDirection::North;
    for (size_t y = 0; y < grid.ySize(); y++)
    {
        for (size_t x = 0; x < grid.xSize(y); x++)
        {
            GridPos current(y, x);

            if (grid.at(current) == '^')
            {
                guard_pos = current;
            }

            std::cout << "Guard facing " << toString(guard_dir) << " at " << current.toString() << '\n';
        }
    }

    while (true)
    {

        char &valRef = grid.getValRef(guard_pos);
        if (valRef != 'X')
        {
            valRef = 'X';
            result++;
        }

        auto maybe_next_pos = grid.getPos(guard_pos, guard_dir);

        if (!maybe_next_pos.has_value())
        {
            std::cout << "Guard exit at " << guard_pos.toString() << '\n';
            break;
        }

        auto next_pos = maybe_next_pos.value();

        auto next_val = grid.at(next_pos);

        if (next_val == '#')
        {
            guard_dir = next(guard_dir);
        }
        else
        {
            guard_pos = next_pos;
        }
    }

    std::cout << grid.toString() << std::endl;
    std::cout << "Result " << result << '\n';

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
