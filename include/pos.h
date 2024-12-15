#ifndef POSITIONS_H
#define POSITIONS_H

#include <iostream>
#include <string>

/**
 * @brief Position in a grid with row (y) and column (x) coordinates.
 */
struct GridPos
{
    int y; // grows down
    int x; // grows right

    GridPos(int y, int x);

    bool operator==(const GridPos &other) const;
    bool operator!=(const GridPos &other) const;

    /**
     * @return "(y,x)"
     */
    std::string toString() const;
};

// Define a custom hash function for GridPos
namespace std
{
    template <>
    struct hash<GridPos>
    {
        std::size_t operator()(const GridPos &pos) const
        {
            return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
        }
    };
}

#endif // POSITIONS_H