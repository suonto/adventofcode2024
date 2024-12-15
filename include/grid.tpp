#include "directions.h"
#include "grid.h"
#include "pos.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>

template <typename T>
Grid<T>::Grid() : _grid(std::vector<std::vector<T>>()) {}

template <typename T>
void Grid<T>::addRow(std::vector<T> row)
{
    _grid.push_back(row);
}

template <typename T>
std::optional<T> Grid<T>::at(const std::optional<GridPos> &pos) const
{

    if (!pos.has_value() || !contains(pos.value()))
    {
        return std::nullopt;
    }

    return _grid[pos.value().y][pos.value().x];
}

template <typename T>
T Grid<T>::at(const GridPos &pos) const
{
    if (!contains(pos))
    {
        throw std::out_of_range("at() grid pos out of range");
    }
    return _grid[pos.y][pos.x];
}

template <typename T>
void Grid<T>::set(const GridPos &pos, T value)
{
    if (!contains(pos))
    {
        throw std::out_of_range("Attempting to set " + pos.toString() + " in a grid of (" + std::to_string(ySize()) + "," + std::to_string(xSize(pos.y)) + ")");
    }

    _grid[pos.y][pos.x] = value;
}

template <typename DirectionType>
void moveHelper(GridPos &pos, const DirectionType &direction, int steps)
{
    if constexpr (std::is_same_v<DirectionType, Direction>)
    {
        switch (direction)
        {
        case Direction::North:
            pos.y -= steps;
            break;
        case Direction::Northeast:
            pos.x += steps;
            pos.y -= steps;
            break;
        case Direction::East:
            pos.x += steps;
            break;
        case Direction::Southeast:
            pos.x += steps;
            pos.y += steps;
            break;
        case Direction::South:
            pos.y += steps;
            break;
        case Direction::Southwest:
            pos.x -= steps;
            pos.y += steps;
            break;
        case Direction::West:
            pos.x -= steps;
            break;
        case Direction::Northwest:
            pos.x -= steps;
            pos.y -= steps;
            break;
        default:
            throw std::invalid_argument("Invalid argument to moveHelper");
        }
    }
    else if constexpr (std::is_same_v<DirectionType, CardinalDirection>)
    {
        switch (direction)
        {
        case CardinalDirection::North:
            pos.y -= steps;
            break;
        case CardinalDirection::East:
            pos.x += steps;
            break;
        case CardinalDirection::South:
            pos.y += steps;
            break;
        case CardinalDirection::West:
            pos.x -= steps;
            break;
        default:
            break;
        }
    }
}

template <typename T>
std::optional<GridPos> Grid<T>::getPos(GridPos pos, const Direction &direction, int steps) const
{
    moveHelper(pos, direction, steps);
    if (contains(pos))
    {
        return pos;
    }
    return std::nullopt;
}

template <typename T>
std::optional<GridPos> Grid<T>::getPos(GridPos pos, const CardinalDirection &direction, int steps) const
{
    moveHelper(pos, direction, steps);
    if (contains(pos))
    {
        return pos;
    }
    return std::nullopt;
}

template <typename T>
bool Grid<T>::move(GridPos &pos, const Direction &d, int steps) const
{
    moveHelper(pos, d, steps);
    return contains(pos);
}

template <typename T>
bool Grid<T>::move(GridPos &pos, const CardinalDirection &d, int steps) const
{
    moveHelper(pos, d, steps);
    return contains(pos);
}

template <typename T, typename DirectionType>
std::optional<T> getValHelper(const Grid<T> &grid, const GridPos &pos, const DirectionType &direction, int steps)
{
    auto next_pos = grid.getPos(pos, direction, steps);

    if (next_pos.has_value())
    {
        return grid.at(next_pos.value());
    }

    return std::nullopt;
}

template <typename T>
std::optional<T> Grid<T>::getVal(const GridPos &pos, const Direction &direction, int steps) const
{
    return getValHelper(*this, pos, direction, steps);
}

template <typename T>
std::optional<T> Grid<T>::getVal(const GridPos &pos, const CardinalDirection &direction, int steps) const
{
    return getValHelper(*this, pos, direction, steps);
}

template <typename T>
T &Grid<T>::getValRef(const GridPos &pos)
{
    if (!contains(pos))
    {
        throw std::out_of_range("getValRef");
    }
    return _grid[pos.y][pos.x];
}

template <typename T>
size_t Grid<T>::ySize() const
{
    return _grid.size();
}

template <typename T>
size_t Grid<T>::xSize(int y) const
{
    return _grid.at(y).size();
}

template <typename T>
std::string Grid<T>::toString() const
{
    std::ostringstream oss;
    for (const std::vector<T> &row : _grid)
    {
        for (const auto &cell : row)
        {
            oss << cell;
        }
        oss << '\n';
    }

    return oss.str();
}

template <typename T>
bool Grid<T>::contains(const GridPos &pos) const
{
    return pos.y >= 0 && pos.y < _grid.size() && pos.x >= 0 && pos.x < _grid[pos.y].size();
}