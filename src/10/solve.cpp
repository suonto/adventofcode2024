#include "pos.h"
#include "grid.h"
#include "10/tile.h"
#include "10/solve.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <optional>

/**
 * Inserts tip Tile into neighbors reachable tips.
 * @return the neighbor tiles that descend by one.
 */
std::vector<Tile> descNeighbors(Grid<Tile> &grid, const Tile &tile, const Tile &tip)
{
    std::vector<Tile> neighbors;
    for (const auto &dir : {CardinalDirection::North, CardinalDirection::East, CardinalDirection::South, CardinalDirection::West})
    {
        auto neighbor_pos = grid.getPos(tile.pos, dir);

        if (!neighbor_pos.has_value())
        {
            continue;
        }

        Tile &neighbor = grid.getValRef(neighbor_pos.value());

        if (neighbor.elevation == tile.elevation - 1)
        {
            neighbor.reachable_tips.insert(tip.pos);
            std::cout << "Tip " << tip.pos.toString() << " is reachable from " << neighbor.pos.toString() << ": " << neighbor.reachable_tips.size() << '\n';
            neighbors.push_back(neighbor);
            std::cout << "after mod: " << grid.at(neighbor.pos).reachable_tips.size() << '\n';
        }
    }

    return neighbors;
}

size_t solve(const std::string &example, bool variant_b)
{
    std::istringstream stream(example);
    std::string line;

    Grid<Tile> grid;

    std::vector<GridPos> tips;
    std::vector<GridPos> trailheads;

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
            if (tile.elevation == 9)
            {
                tips.push_back(tile.pos);
            }
            else if (tile.elevation == 0)
            {
                trailheads.push_back(tile.pos);
            }
        }
        grid.addRow(row);
    }
    std::cout << grid.toString() << '\n';

    for (const auto &tip_pos : tips)
    {
        auto tip = grid.at(tip_pos);
        auto neighbors = descNeighbors(grid, tip, tip);

        while (neighbors.size() > 0)
        {
            auto neighbor = neighbors[0];
            neighbors.erase(neighbors.cbegin());

            for (const auto &new_neighbor : descNeighbors(grid, neighbor, tip))
            {
                neighbors.push_back(new_neighbor);
            }
        }
    }

    size_t result = 0;
    for (const auto &trailhead_pos : trailheads)
    {
        const auto trailhead = grid.at(trailhead_pos);
        std::cout << "trailhead at " << trailhead.pos.toString() << ": " << trailhead.reachable_tips.size() << '\n';
        result += trailhead.reachable_tips.size();
    }

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
