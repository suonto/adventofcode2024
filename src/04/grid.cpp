#include "grid.h"
#include "pos.h"
#include <string>
#include <iostream>

template <typename T>
Grid<T>::Grid() : _grid(std::vector<std::vector<T>>()) {}

template <typename T>
void Grid<T>::addRow(std::vector<T> row)
{
    _grid.push_back(row);
}

template <typename T>
std::optional<T> Grid<T>::at(const GridPos &pos) const
{
    if (y >= 0 && y < _grid.size() && x >= 0 && x < _grid[y].size())
    {
        return _grid[y][x];
    }
    return std::nullopt;
}
template <typename T>
std::optional<GridPos> Grid<T>::nextPos(GridPos pos, const Direction &direction) const
{
    switch (direction)
    {
    case Direction::North:
        pos.y -= 1;
        break;
    case Direction::Northeast:
        pos.x += 1;
        pos.y -= 1;
        break;
    case Direction::East:
        pos.x += 1;
        break;
    case Direction::Southeast:
        pos.x += 1;
        pos.y += 1;
        break;
    case Direction::South:
        pos.y += 1;
        break;
    case Direction::Southwest:
        pos.x -= 1;
        pos.y += 1;
        break;
    case Direction::West:
        pos.x -= 1;
        break;
    case Direction::Northwest:
        pos.x -= 1;
        pos.y -= 1;
        break;
    default:
        return std::nullopt;
    }

    if (pos.y >= 0 && pos.y < _grid.size() && pos.x >= 0 && pos.x < _grid[pos.y].size())
    {
        return pos;
    }
    return std::nullopt;
}