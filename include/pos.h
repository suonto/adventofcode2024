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

    GridPos(int, int);

    bool operator==(const GridPos &other) const;
    bool operator!=(const GridPos &other) const;

    /**
     * @return "(y,x)"
     */
    std::string toString() const;
};

#endif // POSITIONS_H