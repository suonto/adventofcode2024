#include "directions.h"
#include <stdexcept>

// Define the next function for Direction
Direction next(Direction direction)
{
    switch (direction)
    {
    case Direction::North:
        return Direction::Northeast;
    case Direction::Northeast:
        return Direction::East;
    case Direction::East:
        return Direction::Southeast;
    case Direction::Southeast:
        return Direction::South;
    case Direction::South:
        return Direction::Southwest;
    case Direction::Southwest:
        return Direction::West;
    case Direction::West:
        return Direction::Northwest;
    case Direction::Northwest:
        return Direction::North;
    default:
        throw std::invalid_argument("Invalid direction argument");
    }
}

// Define the prev function for Direction
Direction prev(Direction direction)
{
    switch (direction)
    {
    case Direction::North:
        return Direction::Northwest;
    case Direction::Northwest:
        return Direction::West;
    case Direction::West:
        return Direction::Southwest;
    case Direction::Southwest:
        return Direction::South;
    case Direction::South:
        return Direction::Southeast;
    case Direction::Southeast:
        return Direction::East;
    case Direction::East:
        return Direction::Northeast;
    case Direction::Northeast:
        return Direction::North;
    default:
        throw std::invalid_argument("Invalid direction argument");
    }
}

// Define the next function for CardinalDirection
CardinalDirection next(CardinalDirection direction)
{
    switch (direction)
    {
    case CardinalDirection::North:
        return CardinalDirection::East;
    case CardinalDirection::East:
        return CardinalDirection::South;
    case CardinalDirection::South:
        return CardinalDirection::West;
    case CardinalDirection::West:
        return CardinalDirection::North;
    default:
        throw std::invalid_argument("Invalid direction argument");
    }
}

// Define the prev function for CardinalDirection
CardinalDirection prev(CardinalDirection direction)
{
    switch (direction)
    {
    case CardinalDirection::North:
        return CardinalDirection::West;
    case CardinalDirection::West:
        return CardinalDirection::South;
    case CardinalDirection::South:
        return CardinalDirection::East;
    case CardinalDirection::East:
        return CardinalDirection::North;
    default:
        throw std::invalid_argument("Invalid direction argument");
    }
}

// Define the next function for OrdinalDirection
OrdinalDirection next(OrdinalDirection direction)
{
    switch (direction)
    {
    case OrdinalDirection::Northeast:
        return OrdinalDirection::Southeast;
    case OrdinalDirection::Southeast:
        return OrdinalDirection::Southwest;
    case OrdinalDirection::Southwest:
        return OrdinalDirection::Northwest;
    case OrdinalDirection::Northwest:
        return OrdinalDirection::Northeast;
    default:
        throw std::invalid_argument("Invalid direction argument");
    }
}

// Define the prev function for OrdinalDirection
OrdinalDirection prev(OrdinalDirection direction)
{
    switch (direction)
    {
    case OrdinalDirection::Northeast:
        return OrdinalDirection::Northwest;
    case OrdinalDirection::Northwest:
        return OrdinalDirection::Southwest;
    case OrdinalDirection::Southwest:
        return OrdinalDirection::Southeast;
    case OrdinalDirection::Southeast:
        return OrdinalDirection::Northeast;
    default:
        throw std::invalid_argument("Invalid direction argument");
    }
}

// Define the toString function for Direction
std::string toString(Direction direction)
{
    switch (direction)
    {
    case Direction::North:
        return "North";
    case Direction::Northeast:
        return "Northeast";
    case Direction::East:
        return "East";
    case Direction::Southeast:
        return "Southeast";
    case Direction::South:
        return "South";
    case Direction::Southwest:
        return "Southwest";
    case Direction::West:
        return "West";
    case Direction::Northwest:
        return "Northwest";
    default:
        throw std::invalid_argument("Invalid direction argument");
    }
}

// Define the toString function for CardinalDirection
std::string toString(CardinalDirection direction)
{
    switch (direction)
    {
    case CardinalDirection::North:
        return "North";
    case CardinalDirection::East:
        return "East";
    case CardinalDirection::South:
        return "South";
    case CardinalDirection::West:
        return "West";
    default:
        throw std::invalid_argument("Invalid direction argument");
    }
}

// Define the toString function for OrdinalDirection
std::string toString(OrdinalDirection direction)
{
    switch (direction)
    {
    case OrdinalDirection::Northeast:
        return "Northeast";
    case OrdinalDirection::Southeast:
        return "Southeast";
    case OrdinalDirection::Southwest:
        return "Southwest";
    case OrdinalDirection::Northwest:
        return "Northwest";
    default:
        throw std::invalid_argument("Invalid direction argument");
    }
}