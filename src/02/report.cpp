#include "02/report.h"
#include <sstream>
#include <iostream>

Report::Report(std::vector<int> *row) : row(row), inc(1, 3), dec(-3, -1) {}

Report::~Report()
{
    delete row;
}

bool Report::isSafe() const
{
    const Range *range = &dec;
    if (this->isIncreasing())
    {
        range = &inc;
    }

    for (int i = 1; i < this->row->size(); i++)
    {
        int diff = this->row->at(i) - this->row->at(i - 1);
        if (!range->contains(diff))
        {
            return false;
        }
    }

    return true;
}

std::string Report::toString() const
{
    std::ostringstream oss;
    for (int i = 0; i < row->size(); i++)
    {
        oss << row->at(i);
        if (i < row->size() - 1)
        {
            oss << " ";
        }
    }
    return oss.str();
}

bool Report::isIncreasing() const
{
    return this->row->at(0) < this->row->at(1);
}
