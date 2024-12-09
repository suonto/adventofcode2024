#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <03/instruction.h>

int solveA(const char *example)
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
        auto line_result = Instruction(line).processMultiplications();
        result += line_result;
        std::cout << line << '\n';
        std::cout << line_result << " " << result << std::endl;
    }

    return result;
}
