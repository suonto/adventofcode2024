#ifndef VECTOR_H
#define VECTOR_H

#include "pos.h"

class Vector
{
public:
    Vector(const GridPos &start, const GridPos &end);

    const GridPos start;
    const GridPos end;
};

#endif // VECTOR_H