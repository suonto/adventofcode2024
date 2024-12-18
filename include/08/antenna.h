#ifndef ANTENNA_H
#define ANTENNA_H

#include "pos.h"

class Antenna
{
public:
    // Constructor
    Antenna(const GridPos &pos, char frequency);

    const GridPos pos;
    const char frequency;
};

#endif // ANTENNA_H