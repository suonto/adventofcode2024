#ifndef REPORT_H
#define REPORT_H

#include <vector>
#include <string>
#include "range.h"

class Report
{
public:
    Report(int = 0);
    ~Report();
    void pushBack(int);
    bool isSafe();
    std::string toString() const;

private:
    std::vector<int> row;
    std::vector<int> unsafeIndexes;
    int tolerance;
    Range inc;
    Range dec;
    bool isIncreasing() const;
};

#endif // REPORT_H