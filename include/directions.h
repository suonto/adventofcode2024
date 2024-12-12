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
 * @brief Get the string representation of a direction.
 *
 * @param direction The direction to convert to a string.
 * @return const string The string representation of the direction.
 */
std::string toString(Direction);

Direction next(Direction);
CardinalDirection next(CardinalDirection);

#endif // DIRECTIONS_H