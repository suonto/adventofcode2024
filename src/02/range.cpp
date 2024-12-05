#include "02/range.h"

// Range implementation
Range::Range(int min, int max) : min(min), max(max) {}

// inclusive
bool Range::contains(int value) const
{
    return min <= value && value <= max;
}