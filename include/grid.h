#ifndef GRID_H
#define GRID_H

#include <pos.h>
#include <directions.h>

#include <vector>
#include <optional>

/**
 * @brief 2D grid of T.
 *
 * y grows downwards
 * x grows to the right
 */
template <typename T>
class Grid
{
public:
    Grid();
    void addRow(std::vector<T>);
    std::optional<T> at(const GridPos &pos) const;

    std::optional<T> nextVal(const GridPos &currentPos, const Direction &) const;

    /**
     * @param pos is a value (copy) of current pos.
     * Modifies that to return next pos in the given direction.
     */
    std::optional<GridPos> nextPos(GridPos pos, const Direction &) const;

private:
    std::vector<std::vector<T>> _grid;
};

#endif // GRID_H