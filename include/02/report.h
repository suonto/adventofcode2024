#ifndef REPORT_H
#define REPORT_H

#include <vector>
#include <string>
#include "range.h"

class Report
{
public:
    Report(std::vector<int> *row);
    ~Report();
    bool isSafe() const;
    std::string toString() const;

private:
    std::vector<int> *row;
    Range inc;
    Range dec;
    bool isIncreasing() const;
};

#endif // REPORT_H