#include "02/solve.h"
#include "02/report.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

int solve(const std::string &example, int tolerance)
{
    std::istringstream stream(example);
    std::string line;
    std::vector<int> left;
    std::vector<int> right;

    std::vector<Report *> reports;

    while (std::getline(stream, line))
    {
        std::istringstream lineStream(line);
        Report *report = new Report(tolerance);
        int value;
        while (lineStream >> value)
        {
            report->pushBack(value);
        }
        reports.push_back(report);
    }

    int safe_reports = 0;
    for (int i = 0; i < reports.size(); i++)
    {
        bool safe = reports[i]->isSafe();
        auto safeString = safe ? " is safe. Safe reports " : " is not safe. Safe reports ";
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

int solveA(const std::string &example)
{
    return solve(example, 0);
}

int solveB(const std::string &example)
{
    return solve(example, 1);
}
