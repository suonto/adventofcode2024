#include "pos.h"
#include "vector.h"

GridPos::GridPos(size_t y, size_t x) : y(y), x(x) {}

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

GridPos GridPos::operator+(const Vector &v) const
{
    return GridPos(y + v.end.y - v.start.y, x + v.end.x - v.start.x);
}

GridPos GridPos::operator-(const Vector &v) const
{
    return GridPos(y - (v.end.y - v.start.y), x - (v.end.x - v.start.x));
}
