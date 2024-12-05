#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include "02/solve.h"
#include "02/report.h"

int solveA(const char *example)
{
    std::istringstream stream(example);
    std::string line;
    std::vector<int> left;
    std::vector<int> right;

    std::vector<Report *> reports;

    while (std::getline(stream, line))
    {
        std::istringstream lineStream(line);
        std::vector<int> *row = new std::vector<int>();
        int value;
        while (lineStream >> value)
        {
            row->push_back(value);
        }
        Report *report = new Report(row);
        reports.push_back(report);
    }

    int safe_reports = 0;
    for (int i = 0; i < reports.size(); i++)
    {
        bool safe = reports[i]->isSafe();
        auto safeString = safe ? "is safe. Safe reports " : " is not safe. Safe reports ";
        if (safe)
        {
            safe_reports++;
        }
        std::cout << "Report " << i << ": " << reports[i]->toString() << safeString << safe_reports << '\n';
    }

    // Clean up dynamically allocated memory
    for (Report *report : reports)
    {
        delete report;
    }

    return safe_reports;
}