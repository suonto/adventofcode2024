#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <03/instruction.h>

size_t solve(const char *example, bool variant_b)
{
    std::istringstream stream(example);
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

size_t solveA(const char *example)
{
    return solve(example, false);
}

size_t solveB(const char *example)
{
    return solve(example, true);
}
