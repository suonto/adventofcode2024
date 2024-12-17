#include "07/equation.h"

#include <sstream>
#include <iostream>
#include <optional>
#include <cmath>

size_t multiplier(size_t n)
{
    return std::pow(10, std::to_string(n).size());
}

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
    else if (result >= last && nums.size() > 0)
    {
        valid += Equation(result - last, nums).validate();
    }

    return valid;
}

size_t Equation::validate_b() const
{

    size_t valid = 0;

    // nums is a mutable copy
    // 3: 1 + 2
    // 6: 1 + 2 + 3
    std::vector<size_t> nums = numbers;
    size_t last = nums[nums.size() - 1];
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
        valid += Equation(result / last, nums).validate_b();
    }

    if (result == last && nums.size() == 0)
    {
        valid += 1;
    }
    else if (result >= last && nums.size() > 0)
    {
        valid += Equation(result - last, nums).validate_b();
    }

    // Concat and do the same
    if (nums.size() > 0)
    {
        std::vector<size_t> nums2 = nums;
        size_t second_last = nums2[nums2.size() - 1];
        nums2.pop_back();

        size_t concat = std::stoul(std::to_string(second_last) + std::to_string(last));
        nums2.push_back(concat);

        // right side concat +
        if (result % concat == 0 && nums2.size() == 1 && result / concat == nums2[0])
        {
            valid += 1;
        }
        else if (result % concat == 0 && nums2.size() > 0)
        {
            valid += Equation(result / concat, nums2).validate_b();
        }

        //  right side concat *
        if (result == concat && nums2.size() == 0)
        {
            valid += 1;
        }
        else if (result >= concat && nums2.size() > 0)
        {
            valid += Equation(result - concat, nums2).validate_b();
        }

        // left side concat +
        if (nums2.size() == 1 && (result - last) / multiplier(last) == second_last)
        {
            valid += 1;
        }
        if ((result - last) % multiplier(last) == 0 && nums2.size() > 1)
        {
            valid += Equation((result - last) / multiplier(last), nums2).validate_b();
        }

        // left side concat *
        if (nums2.size() == 1 && (result / (last * multiplier(last))) == second_last)
        {
            valid += 1;
        }
        if (nums2.size() > 1 && (result % (last * multiplier(last))) == 0)
        {
            valid += Equation((result / (last * multiplier(last))), nums2).validate_b();
        }
    }

    return valid;
}
