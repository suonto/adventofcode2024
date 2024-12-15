#ifndef DIRECTIONS_H
#define DIRECTIONS_H

#include <string>

/**
 * @brief Enumeration representing only the cardinal directions.
 */
enum class CardinalDirection
{
    North,
    East,
    South,
    West
};

/**
 * @brief Enumeration representing the cardinal and primary ordinal directions.
 */
enum class Direction
{
    North,
    Northeast,
    East,
    Southeast,
    South,
    Southwest,
    West,
    Northwest
};

/**
 * @brief Enumeration representing only the primary ordinal directions.
 */
enum class OrdinalDirection
{
    Northeast,
    Southeast,
    Southwest,
    Northwest
};

Direction next(Direction direction);
Direction prev(Direction direction);

CardinalDirection next(CardinalDirection direction);
CardinalDirection prev(CardinalDirection direction);

OrdinalDirection next(OrdinalDirection direction);
OrdinalDirection prev(OrdinalDirection direction);

std::string toString(Direction direction);
std::string toString(CardinalDirection direction);
std::string toString(OrdinalDirection direction);

#endif // DIRECTIONS_H