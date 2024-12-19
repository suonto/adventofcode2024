#ifndef TILE_H
#define TILE_H

#include <ostream>
#include "pos.h"

/**
 * Trail tile.
 */
struct Tile
{
    const size_t elevation;
    size_t paths;
    const GridPos pos;

    Tile() = delete;
    Tile(const GridPos pos, size_t elevation);
};

std::ostream &operator<<(std::ostream &os, const Tile &tile);

#endif // TILE_H