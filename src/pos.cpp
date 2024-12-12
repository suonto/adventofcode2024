#include "pos.h"

GridPos::GridPos(int y, int x) : y(y), x(x) {}

bool GridPos::operator==(const GridPos &other) const
{
    return x == other.x && y == other.y;
}

bool GridPos::operator!=(const GridPos &other) const
{
    return !(*this == other);
}

std::string GridPos::toString() const
{
    return "(" + std::to_string(y) + ", " + std::to_string(x) + ")";
}