#include "02/report.h"
#include <sstream>
#include <iostream>
#include <algorithm>

Report::Report(int tolerance) : row(std::vector<int>()), tolerance(tolerance), unsafeIndexes(std::vector<int>()), inc(1, 3), dec(-3, -1) {}

Report::~Report() {}

void Report::pushBack(int n)
{
    row.push_back(n);
}

bool Report::isSafe()
{
    bool result = true;
    const Range *range = &dec;
    if (this->isIncreasing())
    {
        range = &inc;
    }

    size_t margin = tolerance;

    for (size_t i = 1; i < row.size(); i++)
    {
        int diff = row.at(i) - row.at(i - 1);

        if (!range->contains(diff))
        {
            if (margin == 0)
            {
                result = false;
                break;
            }
            margin--;
            int unsafe_index = -1;

            // remove i if there is no i+1 or i-1 is connected to i+1
            if (i + 1 == row.size() || range->contains(row.at(i + 1) - row.at(i - 1)))
            {
                unsafe_index = i;
            }

            // remove i-1 if there's no i-2 or i-2 is conneted to i
            else if (i < 2 || range->contains(row.at(i) - row.at(i - 2)))
            {
                unsafe_index = i - 1;
            }

            else
            {
                std::cout << this->toString() << " is not safe by removing " << i << " or " << i - 1 << std::endl;
                result = false;
                break;
            }

            // remove one
            unsafeIndexes.push_back(unsafe_index);
            std::cout << this->toString() << " at index " << i << " add unsafe index " << unsafe_index << " number " << row.at(unsafe_index) << std::endl;

            // skip next index, already processed
            if (unsafe_index == i)
            {
                i++;
            }
        }
    }

    std::cout << this->toString() << " safe? " << result << std::endl;

    return result;
}

std::string Report::toString() const
{
    std::ostringstream oss;
    for (int i = 0; i < row.size(); i++)
    {
        oss << row.at(i);
        if (i < row.size() - 1)
        {
            oss << " ";
        }
    }
    return oss.str();
}

bool Report::isIncreasing() const
{
    int increasing = 0;
    for (size_t i = 1; i < row.size(); i++)
    {
        if (this->row.at(i - 1) < this->row.at(i))
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
