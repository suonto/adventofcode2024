#include "04/letter.h"
#include <ostream>

std::ostream &operator<<(std::ostream &os, const Letter &letter)
{
    if (letter.enabled)
    {
        os << letter.c;
    }
    else
    {
        os << '.';
    }
    return os;
}