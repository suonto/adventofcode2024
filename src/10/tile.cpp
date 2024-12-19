#include "10/tile.h"
#include "pos.h"

Tile::Tile(const GridPos pos, size_t elevation) : pos(pos), elevation(elevation), reachable_tips() {}

std::ostream &operator<<(std::ostream &os, const Tile &tile)
{
    os << tile.elevation;
    return os;
}