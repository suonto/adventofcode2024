#include "02/report.h"
#include <sstream>
#include <iostream>
#include <algorithm>

Report::Report(std::vector<int> *row, int tolerance) : row(row), tolerance(tolerance), inc(1, 3), dec(-3, -1) {}

Report::~Report()
{
    delete row;
}

bool Report::isSafe() const
{
    bool result = true;
    const Range *range = &dec;
    if (this->isIncreasing())
    {
        range = &inc;
    }

    int margin = tolerance;

    for (int i = 1; i < row->size(); i++)
    {
        int diff = row->at(i) - row->at(i - 1);
        if (!range->contains(diff))
        {
            if (margin == 0)
            {
                result = false;
                break;
            }
            margin--;
            std::cout << this->toString(row) << " removing index " << i << " number " << row->at(i) << std::endl;
            row->erase(row->begin() + i);
            i--; // Adjust the index to account for the removed element
        }
    }

    std::cout << this->toString(row) << " safe? " << result << std::endl;

    return result;
}

std::string Report::toString() const
{
    return this->toString(row);
}

std::string Report::toString(std::vector<int> *row) const
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
    int increasing = 0;
    for (int i = 1; i < row->size(); i++)
    {
        if (this->row->at(0) < this->row->at(1))
        {
            increasing++;
        }
        if (increasing > tolerance)
        {
            return true;
        }
    }
    return false;
}
