#include "07/equation.h"

#include <sstream>
#include <iostream>
#include <optional>
#include <cmath>

size_t multiplier(size_t n)
{
    return std::pow(10, std::to_string(n).size());
}

Equation::Equation(size_t result, const std::vector<size_t> &numbers, size_t depth)
    : result(result), numbers(numbers), depth(depth) {}

std::string Equation::toString() const
{
    std::ostringstream oss;
    for (size_t i = 0; i < depth; i++)
    {
        oss << "  ";
    }
    oss << result << ": ";
    for (size_t number : numbers)
    {
        oss << number << " ";
    }
    return oss.str();
}

bool Equation::validate() const
{
    std::vector<size_t> nums = numbers;
    size_t last = numbers[numbers.size() - 1];
    nums.pop_back();

    std::cout << this->toString() << '\n';

    if (result % last == 0 && nums.size() == 1 && result / last == nums[0])
    {
        return true;
    }
    else if (result % last == 0 && nums.size() > 0)
    {
        if (Equation(result / last, nums).validate())
        {
            return true;
        };
    }

    if (result == last && nums.size() == 0)
    {
        return true;
    }
    else if (result >= last && nums.size() > 0)
    {
        if (Equation(result - last, nums).validate())
        {
            return true;
        };
    }

    return false;
}

bool Equation::validate_b() const
{
    std::vector<size_t> nums = numbers;
    size_t last = nums[nums.size() - 1];
    nums.pop_back();

    std::cout << this->toString() << '\n';

    if (result % last == 0 && nums.size() == 1 && result / last == nums[0])
    {
        std::cout << "return at *\n";
        return true;
    }
    else if (result % last == 0 && nums.size() > 1)
    {
        std::cout << "recurse at * \n";
        if (Equation(result / last, nums, depth + 1).validate_b())
        {
            return true;
        }
    }

    if (result == last && nums.size() == 0)
    {
        std::cout << "return at -\n";
        return true;
    }
    else if (result >= last && nums.size() > 0)
    {
        std::cout << "recurse at - \n";
        if (
            Equation(result - last, nums, depth + 1).validate_b())
        {
            return true;
        }
    }

    if (nums.size() >= 1 && (result - last) % multiplier(last) == 0)
    {
        std::cout << "recurse at left side concat +\n";
        if (Equation((result - last) / multiplier(last), nums, depth + 1).validate_b())
        {
            return true;
        }
    }

    return false;
}
