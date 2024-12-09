#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// #include <vector>
#include <string>

class Instruction
{
public:
    Instruction(std::string);
    // ~Instruction();
    size_t processMultiplications();

private:
    std::string raw;
};

#endif // INSTRUCTION_H