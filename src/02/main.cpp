#include "02/main.h"
#include "02/solve.h"

#include <iostream>
#include <string>

std::string input = R"(7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9)";

int main()
{
    std::cout << "01 main solving input" << std::endl;
    // solve(input);
    // 523 too high
    return solve(input, 1);
}