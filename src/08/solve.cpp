#include "pos.h"
#include "08/antenna.h"
#include "vector.h"
#include "grid.h"
#include "08/solve.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <optional>
#include <unordered_map>
#include <unordered_set>

size_t solve(const std::string &example, bool variant_b)
{
    std::istringstream stream(example);
    std::string line;
    std::unordered_map<char, std::vector<Antenna>> groups;

    // Grid for visualizations only
    Grid<char> grid;

    std::cout << '\n';
    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            continue;
        };

        std::vector<char> row;
        for (size_t i = 0; i < line.size(); i++)
        {
            auto freq = line[i];
            if (line[i] != '.')
            {
                groups[freq].push_back(Antenna({grid.ySize(), i}, freq));
            }
            row.push_back(freq);
        }
        grid.addRow(row);
    }

    std::cout << grid.toString() << '\n';

    std::unordered_set<GridPos> antinodes;

    for (const auto &[freq, antennas] : groups)
    {
        std::cout << "processing group " << freq << '\n';
        for (size_t i = 0; i < antennas.size(); i++)
        {
            Antenna current = antennas[i];
            for (size_t j = i + 1; j < antennas.size(); j++)
            {
                Antenna other = antennas[j];
                Vector vec(current.pos, other.pos);

                if (variant_b)
                {
                    GridPos backwards = current.pos;
                    GridPos forwards = other.pos;
                    antinodes.insert(forwards);
                    while (grid.contains(backwards))
                    {
                        antinodes.insert(backwards);
                        backwards = backwards - vec;
                    }

                    while (grid.contains(forwards))
                    {
                        antinodes.insert(forwards);
                        forwards = forwards + vec;
                    }
                }
                else
                {
                    if (grid.contains(current.pos - vec))
                    {
                        auto pos1 = current.pos - vec;
                        // std::cout << "antinode " << freq << " at " << (pos1).toString() + '\n';
                        antinodes.insert(pos1);
                    }
                    if (grid.contains(other.pos + vec))
                    {
                        auto pos2 = other.pos + vec;
                        // std::cout << "antinode " << freq << " at " << (pos2).toString() + '\n';
                        antinodes.insert(pos2);
                    }
                }
            }
        }
    }

    std::cout << "Result " << antinodes.size() << std::endl;

    return antinodes.size();
}

size_t solveA(const std::string &example)
{
    return solve(example, false);
}

size_t solveB(const std::string &example)
{
    return solve(example, true);
}
