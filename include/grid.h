#ifndef GRID_H
#define GRID_H

#include <pos.h>
#include <directions.h>

#include <vector>
#include <optional>
#include <string>

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

    /**
     * For pos maybe in the grid.
     */
    std::optional<T> at(const std::optional<GridPos> &pos) const;

    /**
     * For pos definitely in the grid.
     */
    T at(const GridPos &pos) const;
    void set(const GridPos &pos, T value);

    /**
     * @return the val (if any) n steps in direction d from current pos.
     */
    std::optional<T> getVal(const GridPos &currentPos, const Direction &d, int steps = 1) const;
    std::optional<T> getVal(const GridPos &currentPos, const CardinalDirection &d, int steps = 1) const;

    /**
     * @return the val ref at current pos.
     */
    T &getValRef(const GridPos &currentPos);

    /**
     * @param pos is a value (copy) of current pos.
     * Modifies that to return pos some steps in the given direction.
     */
    std::optional<GridPos> getPos(GridPos pos, const Direction &, int steps = 1) const;
    std::optional<GridPos> getPos(GridPos pos, const CardinalDirection &, int steps = 1) const;

    /**
     * @param mutable reference to pos instance which will be moved (altered).
     * @param direction to move towards.
     * @param steps how much. Can be negative.
     */
    bool move(GridPos &pos, const Direction &d, int steps = 1) const;
    bool move(GridPos &pos, const CardinalDirection &d, int steps = 1) const;

    size_t ySize() const;
    size_t xSize(int y = 0) const;
    std::string toString() const;

private:
    std::vector<std::vector<T>> _grid;

    bool contains(const GridPos &pos) const;
};

#include <grid.tpp>

#endif // GRID_H