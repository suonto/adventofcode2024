#include "pos.h"
#include "grid.h"
#include "10/tile.h"
#include "10/solve.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <optional>

size_t solve(const std::string &example, bool variant_b)
{
    std::istringstream stream(example);
    std::string line;

    Grid<Tile> grid;

    std::vector<Tile> tips;

    std::cout << '\n';
    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            continue;
        };

        std::vector<Tile> row;
        for (size_t i = 0; i < line.size(); i++)
        {
            Tile tile = Tile(GridPos({grid.ySize(), i}), static_cast<size_t>(line[i] - '0'));
            row.push_back(tile);
            if (tile.elevation == 9){
                tips.push_back(tile);
            }
        }
        grid.addRow(row);
    }

    std::cout << grid.toString() << '\n';

    size_t result = 0;

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
