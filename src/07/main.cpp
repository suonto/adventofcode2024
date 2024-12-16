#include <iostream>
#include <string>

#include "06/main.h"
#include "06/solve.h"

const std::string example = R"(
190: 10 19
3267: 81 40 27
83: 17 5
156: 15 6
7290: 6 8 6 15
161011: 16 10 13
192: 17 8 14
21037: 9 7 18 13
292: 11 6 16 20
)";

void print_usage()
{
    std::cerr << "Usage: <program> <variant>" << std::endl;
    std::cerr << "Variant must be A or B." << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        print_usage();
        return 1;
    }

    std::string variant = argv[1];

    std::cout << argv[0] << " solving input" << std::endl;
    size_t result;
    if (variant == "A")
    {
        result = solveA(example);
    }
    else if (variant == "B")
    {
        result = solveB(example);
    }
    else
    {
        throw std::invalid_argument("Invalid variant");
    }

    std::cout << "Result: " << result << std::endl;
    return 0;
}