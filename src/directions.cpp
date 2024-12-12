#include "directions.h"

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
    }
}

Direction operator++(Direction &direction)
{
    direction = static_cast<Direction>((static_cast<int>(direction) + 1) % 8);
    return direction;
}

Direction operator--(Direction &direction)
{
    direction = static_cast<Direction>((static_cast<int>(direction) - 1) % 8);
    return direction;
}

CardinalDirection operator++(CardinalDirection &direction)
{
    direction = static_cast<CardinalDirection>((static_cast<int>(direction) + 1) % 4);
    return direction;
}

CardinalDirection operator++(CardinalDirection &direction)
{
    direction = static_cast<CardinalDirection>((static_cast<int>(direction) - 1) % 4);
    return direction;
}
