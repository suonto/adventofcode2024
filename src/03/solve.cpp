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
        result += Instruction(line).processMultiplications();
    }

    return result;
}
