#include <iostream>
#include "03/main.h"
#include "03/solve.h"

const char *input = R"(xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5)))";

int main()
{
    std::cout << "03 main solving input" << std::endl;
    // auto result = solveA(input);
    auto result = solveB(input);
    return result;
}