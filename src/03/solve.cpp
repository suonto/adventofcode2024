#include <03/instruction.h>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

size_t solve(const std::string &example, bool variant_b)
{
    std::istringstream stream;
    stream.str(example);
    std::string line;
    size_t result = 0;

    std::vector<Instruction *> instructions;

    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            continue;
        }
        auto line_result = Instruction(line, variant_b).processMultiplications();
        result += line_result;
        std::cout << line << '\n';
        std::cout << line_result << " " << result << std::endl;
    }

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
