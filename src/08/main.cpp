#include <iostream>
#include <string>

#include "08/main.h"
#include "08/solve.h"

const std::string example = R"(
............
........0...
.....0......
.......0....
....0.......
......A.....
............
............
........A...
.........A..
............
............
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
