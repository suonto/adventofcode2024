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

    for (size_t i = 3; i < raw.size(); i++)
    {
        std::cout << "substring at " << i - 3 << ": " << raw.substr(i - 3, 3) << '\n';
        if (raw.substr(i - 3, 3) == "do(")
        {
            multiply = true;
            std::cout << "multiply at " << i - 3 << '\n';
        }

        if (variant_b && i > 6 && raw.substr(i - 6, 6) == "don't(")
        {
            multiply = false;
        }

        if (multiply && i > 4 && raw.substr(i - 4, 4) == "mul(")
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
