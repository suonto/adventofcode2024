#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// #include <vector>
#include <string>

class Instruction
{
public:
    Instruction(std::string, bool = false);
    // ~Instruction();
    size_t processMultiplications();

private:
    std::string raw;
    bool variant_b;
};

#endif // INSTRUCTION_H