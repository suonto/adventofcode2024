#ifndef LETTER_H
#define LETTER_H

#include <ostream>

struct Letter
{
    char c;
    bool enabled;

    Letter(char c) : c(c), enabled(false) {}
};

std::ostream &operator<<(std::ostream &os, const Letter &letter);

#endif // LETTER_H