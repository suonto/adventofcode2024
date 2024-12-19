#ifndef TILE_H
#define TILE_H

#include "pos.h"

#include <ostream>
#include <vector>
#include <unordered_set>

/**
 * Trail tile.
 */
struct Tile
{
    size_t elevation;
    std::unordered_set<GridPos> reachable_tips;
    GridPos pos;

    Tile() = delete;
    Tile(const GridPos pos, size_t elevation);
};

std::ostream &operator<<(std::ostream &os, const Tile &tile);

// Define a custom hash function for GridPos
namespace std
{
    template <>
    struct hash<Tile>
    {
        std::size_t operator()(const Tile &tile) const
        {
            return std::hash<int>()(tile.pos.x) ^ (std::hash<int>()(tile.pos.y) << 1);
        }
    };
}

#endif // TILE_H