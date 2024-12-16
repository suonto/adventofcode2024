#include "07/solve.h"
#include "07/equation.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

size_t solve(const std::string &example, bool variant_b)
{
    std::istringstream stream(example);
    std::string line;
    size_t result = 0;

    std::vector<Equation> equations;

    std::cout << '\n';
    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::istringstream line_stream(line);
        size_t key;
        char colon;
        line_stream >> key >> colon;

        std::vector<size_t> values;
        size_t value;
        while (line_stream >> value)
        {
            values.push_back(value);
        }

        equations.push_back(Equation(key, values));
    }

    // print the parsed equations
    for (const auto &eq : equations)
    {
        auto res = eq.validate();
        if (res > 0)
        {
            result += eq.result;
        }
        std::cout << eq.toString() << " += " << res << " = " << result << '\n';
    }

    std::cout << "Result " << result << std::endl;

    return result;
}

size_t solveA(const std::string &example)
{
    return solve(example, false);
}

size_t solveB(const std::string &example)
{
    return solve(example, true);
}