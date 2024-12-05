#ifndef REPORT_H
#define REPORT_H

#include <vector>
#include <string>
#include "range.h"

class Report
{
public:
    Report(std::vector<int> *, int = 0);
    ~Report();
    bool isSafe() const;
    std::string toString() const;

private:
    std::vector<int> *row;
    std::vector<int> *safeRow;
    int tolerance;
    Range inc;
    Range dec;
    bool isIncreasing() const;
    std::string toString(std::vector<int> *) const;
};

#endif // REPORT_H