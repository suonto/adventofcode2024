#include "07/equation.h"

#include <sstream>
#include <iostream>

Equation::Equation(size_t result, const std::vector<size_t> &numbers)
    : result(result), numbers(numbers) {}

std::string Equation::toString() const
{
    std::ostringstream oss;
    oss << result << ": ";
    for (size_t number : numbers)
    {
        oss << number << " ";
    }
    return oss.str();
}

size_t Equation::validate() const
{

    size_t valid = 0;

    // nums is a mutable copy
    std::vector<size_t> nums = numbers;
    size_t last = numbers[numbers.size() - 1];
    nums.pop_back();

    std::cout << this->toString() << '\n';
    // std::cout << "reminder: " << result % last << '\n';
    // std::cout << "division: " << result / last << '\n';
    // std::cout << "difference: " << result - last << '\n';

    if (result % last == 0 && nums.size() == 1 && result / last == nums[0])
    {
        valid += 1;
    }
    else if (result % last == 0 && nums.size() > 0)
    {
        valid += Equation(result / last, nums).validate();
    }

    if (result == last && nums.size() == 0)
    {
        valid += 1;
    }
    else if (result - last >= 0 && nums.size() > 0)
    {
        valid += Equation(result - last, nums).validate();
    }

    return valid;
}
