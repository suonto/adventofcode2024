#include <iostream>
#include <string>

#include "06/main.h"
#include "06/solve.h"

const std::string example = R"(
2333133121414131402
)";

const std::string example2 = R"(
12345
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