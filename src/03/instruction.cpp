#include "03/instruction.h"
#include <string>
#include <iostream>

Instruction::Instruction(std::string s, bool variant_b) : raw(s), variant_b(variant_b) {}

size_t Instruction::processMultiplications()
{
    size_t result = 0;
    size_t xPos = 0;
    size_t x = 0;
    size_t yPos = 0;
    size_t y = 0;
    bool multiply = true;

    for (size_t i = 4; i < raw.size(); i++)
    {
        // std::cout << i << " " << raw.substr(i - 4, 4) << '\n';
        if (variant_b && raw.substr(i - 4, 4) == "do()")
        {
            multiply = true;
            std::cout << "do() at " << i - 4 << '\n';
        }

        if (variant_b && i >= 7 && raw.substr(i - 7, 7) == "don't()")
        {
            multiply = false;
            std::cout << "don't() at " << i - 7 << '\n';
        }

        if (multiply && raw.substr(i - 4, 4) == "mul(")
        {
            xPos = i;
        }

        if (xPos > 0 && !std::isdigit(raw[i]))
        {
            if (raw[i] == ',' && i > xPos)
            {
                x = std::stoi(raw.substr(xPos, i - xPos));
                // std::cout << "x at " << xPos << " = " << x << '\n';
                yPos = i + 1;
            }
            xPos = 0;
        }

        if (yPos > 0 && i >= yPos && !std::isdigit(raw[i]))
        {
            if (raw[i] == ')' && i > yPos)
            {
                y = std::stoi(raw.substr(yPos, i - yPos));
                // std::cout << "y at " << yPos << " = " << y << '\n';
                auto product = x * y;
                result += product;
                std::cout << x << " * " << y << " = " << product << ", result = " << result << '\n';
            }
            yPos = 0;
        }
    }

    std::cout << std::endl;

    return result;
}
