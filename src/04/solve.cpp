#include "grid.h"
#include "pos.h"
#include "directions.h"
#include "04/letter.h"
#include "04/solve.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <optional>

size_t tryAtB(Grid<Letter> &grid, const GridPos &currentPos)
{
    // Create a map of direction, word
    std::map<Direction, bool> result;

    auto current = grid.at(currentPos);

    if (current.c != 'A')
    {
        return 0;
    }

    std::vector<Direction> ordinals = {Direction::Northeast, Direction::Southeast, Direction::Southwest, Direction::Northwest};

    // Insert initial char for each direction
    for (auto d : ordinals)
    {
        result[d] = false;
    }

    for (auto it = result.cbegin(); it != result.cend();)
    {
        auto dir = it->first;
        GridPos cursor = currentPos;

        auto prev = grid.getVal(currentPos, dir, -1).value_or('#');
        auto next = grid.getVal(currentPos, dir, 1).value_or('#');

        if (prev.c == 'M' && next.c == 'S')
        {
            it++;
        }
        else
        {
            it = result.erase(it);
        }
    }

    if ((result.find(Direction::Northeast) != result.end() || result.find(Direction::Southwest) != result.end()) && (result.find(Direction::Southeast) != result.end() || result.find(Direction::Northwest) != result.end()))
    {
        Letter &letterRef = grid.getValRef(currentPos);
        letterRef.enabled = true;
        std::cout << "enabled " << currentPos.toString() << '\n';

        for (auto ord : ordinals)
        {
            auto enable_pos = grid.getPos(currentPos, ord);
            if (!enable_pos.has_value())
            {
                std::logic_error("Enable out of bounds");
            }
            Letter &letterRef = grid.getValRef(enable_pos.value());
            letterRef.enabled = true;
            std::cout << "enabled " << enable_pos.value().toString() << '\n';
        }

        return 1;
    }
    else
    {
        return 0;
    }
}

size_t tryAt(Grid<Letter> &grid, const GridPos &currentPos, const std::string &word)
{
    // Create a map of direction, word
    std::map<Direction, std::string> result;

    auto current = grid.at(currentPos);

    if (current.c != word[0])
    {
        return 0;
    }

    // Insert initial char for each direction
    result[Direction::Northeast] = current.c;
    result[Direction::East] = current.c;
    result[Direction::Southeast] = current.c;
    result[Direction::South] = current.c;

    for (auto it = result.cbegin(); it != result.cend();)
    {
        auto dir = it->first;
        GridPos cursor = currentPos;
        bool erased = false;
        for (size_t i = 1; i < word.size(); i++)
        {
            std::cout << currentPos.toString() << " cursor " << cursor.toString() << " moving " << toString(dir) << '\n';
            if (!grid.move(cursor, dir))
            {
                it = result.erase(it);
                erased = true;
                break;
            }

            auto next = grid.at(cursor);
            std::cout << currentPos.toString() << " " << toString(dir) << " " << i << " " << cursor.toString() << " next: " << next.c << '\n';
            if (next.c == word[i])
            {
                result[dir] += word[i];
                std::cout << currentPos.toString() << " " << toString(dir) << " " << i << " " << cursor.toString() << ": " << result[dir] << '\n';
            }
            else
            {
                it = result.erase(it);
                erased = true;
                break;
            }
        }
        if (!erased)
        {
            it++;
        }
    }

    if (result.size() > 0)
    {
        for (auto it = result.cbegin(); it != result.cend(); it++)
        {
            auto dir = it->first;
            for (size_t i = 0; i < word.size(); i++)
            {
                auto enable_pos = grid.getPos(currentPos, dir, i);
                if (!enable_pos.has_value())
                {
                    std::logic_error("Enable out of bounds");
                }
                Letter &letterRef = grid.getValRef(enable_pos.value());
                letterRef.enabled = true;
                std::cout << "enabled " << enable_pos.value().toString() << '\n';
            }
        }
        return result.size();
    }
    else
    {
        return 0;
    }
}

size_t solve(const std::string &example, bool variant_b)
{
    std::istringstream stream(example);
    std::string line;
    size_t result = 0;

    Grid<Letter> grid;

    std::cout << '\n';
    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            continue;
        };
        std::vector<Letter> row;
        for (char c : line)
        {
            row.push_back(Letter(c));
        }

        grid.addRow(row);
        std::cout << line << '\n';
    }

    std::cout << '\n'
              << "Trying grid cells" << '\n';

    for (size_t y = 0; y < grid.ySize(); y++)
    {
        for (size_t x = 0; x < grid.xSize(y); x++)
        {
            GridPos current(y, x);
            // not very optimized lolz
            size_t cell_result;
            if (variant_b)
            {
                cell_result = tryAtB(grid, current);
            }
            else
            {
                cell_result = tryAt(grid, current, "XMAS") + tryAt(grid, current, "SAMX");
            }
            std::cout << current.toString() << " cell result " << cell_result << '\n';
            if (cell_result != 0)
            {
                result += cell_result;
                std::cout << current.toString() << " result + " << cell_result << " = " << result << '\n';
            }
        }
    }
    std::cout << '\n'
              << "Result " << result << '\n'
              << '\n';
    std::cout << grid.toString() << std::endl;

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
