#include "01/main.h"
#include "01/solve.h"

#include <iostream>
#include <string>

const std::string input = R"(
3   4
4   3
2   5
1   3
3   9
3   3
)";

int main()
{
    std::cout << "01 main solving input" << std::endl;
    auto result = solve2(input);
    return result;
}