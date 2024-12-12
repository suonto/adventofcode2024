#include <grid.h>
#include <directions.h>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <optional>

std::optional<char> next(Grid<char> *grid, std::string direction, int y, int x)
{
    // TODO
}

void tryAt(Grid<char> *grid, std::string word, int y, int x)
{
    // Create a map of direction, word
    std::map<Direction, std::string> result;

    auto current = grid->at(GridPos(y, x));

    if (!current.has_value() || current.value() != word[0])
    {
        return;
    }

    // Insert initial char for each direction
    result[Direction::East] = current.value();
    result[Direction::Southeast] = current.value();
    result[Direction::South] = current.value();

    // iterate from second char forward
    for (size_t i = 1; i < word.size(); i++)
    {
        for (const auto &[direction, str] : result)
        {
        }
    }
}

size_t solve(const char *example, bool variant_b)
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
        grid.addRow(std::vector<char>(line.begin(), line.end()));
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
