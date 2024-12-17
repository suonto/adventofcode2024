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

bool Equation::validate() const
{

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
    // nums is a mutable copy
    // 3: 1 + 2
    // 6: 1 + 2 + 3
    std::vector<size_t> nums = numbers;
    size_t last = nums[nums.size() - 1];
    nums.pop_back();

    std::cout << this->toString() << '\n';

    if (result % last == 0 && nums.size() == 1 && result / last == nums[0])
    {
        return true;
    }
    else if (result % last == 0 && nums.size() > 0 && Equation(result / last, nums).validate_b())
    {
        return true;
    }

    if (result == last && nums.size() == 0)
    {
        return true;
    }
    else if (result >= last && nums.size() > 0 && Equation(result - last, nums).validate_b())
    {
        return true;
    }

    // left side concat +
    if (nums.size() == 1 && (result - last) % multiplier(last) == 0 && (result - last) / multiplier(last) == nums[0])
    {
        return true;
    }
    if (nums.size() > 1 && (result - last) % multiplier(last) == 0 && Equation((result - last) / multiplier(last), nums).validate_b())
    {
        return true;
    }

    // left side concat *
    if (nums.size() == 1 && (result % (last * multiplier(last))) == 0 && (result / (last * multiplier(last))) == nums[0])
    {
        return true;
    }
    if (nums.size() > 1 && (result % (last * multiplier(last))) == 0 && Equation((result / (last * multiplier(last))), nums).validate_b())
    {
        return true;
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
            return true;
        }
        else if (result % concat == 0 && nums2.size() > 0 && Equation(result / concat, nums2).validate_b())
        {
            return true;
        }

        //  right side concat *
        if (result == concat && nums2.size() == 0)
        {
            return true;
        }
        else if (result >= concat && nums2.size() > 0 && Equation(result - concat, nums2).validate_b())
        {
            return true;
        }
    }

    return false;
}
