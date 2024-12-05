#ifndef RANGE_H
#define RANGE_H

class Range
{
public:
    Range(int min, int max);

    bool contains(int value) const;

private:
    int min;
    int max;
};

#endif // RANGE_H