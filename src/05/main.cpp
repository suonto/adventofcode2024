#include <iostream>
#include <string>

#include "05/main.h"
#include "05/solve.h"

const std::string example = R"(
47|53
97|13
97|61
97|47
75|29
61|13
75|53
29|13
97|29
53|29
61|53
97|53
61|29
47|13
75|47
97|75
47|61
75|61
47|29
75|13
53|13

75,47,61,53,29
97,61,53,29,13
75,29,13
75,97,47,61,53
61,13,29
97,13,75,29,47
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