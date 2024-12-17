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
    for (size_t i = 0; i < depth ;i++) {
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

    // left side concat +
    // 486: 6 8 6 -> 480/10: 48
    // last = 6, nums = 6, 8
    // eq 48: 48
    if (nums.size() >= 2 && (result - last) % multiplier(last) == 0)
    {
        std::cout << "recurse at left side concat +\n";
        std::vector<size_t> nums2 = nums;
        size_t concat = std::stoul(std::to_string(nums2[nums2.size() - 2]) + std::to_string(nums2[nums2.size()-1]));
        nums2.pop_back();
        nums2.pop_back();
        nums2.push_back(concat);
        if (Equation((result - last) / multiplier(last), nums2, depth + 1).validate_b())
        {
            return true;
        }
        if (Equation((result - last) / multiplier(last), nums, depth + 1).validate_b())
        {
            return true;
        }
    }

    // left side concat *
    if (nums.size() >= 2 && (result % (last * multiplier(last))) == 0)
    {
        std::cout << "recurse at left side concat *\n";
        std::vector<size_t> nums2 = nums;
        size_t concat = std::stoul(std::to_string(nums2[nums2.size() - 2]) + std::to_string(nums2[nums2.size()-1]));
        nums2.pop_back();
        nums2.pop_back();
        nums2.push_back(concat);
        nums2.push_back(concat);
        if (Equation((result / (last * multiplier(last))), nums2, depth + 1).validate_b())
        {
            return true;
        }
        if (Equation((result / (last * multiplier(last))), nums,depth + 1).validate_b())
        {
            return true;
        }
    }

    // Concat and do the same
    if (nums.size() > 0)
    {
        std::vector<size_t> nums2 = nums;
        size_t second_last = nums2[nums2.size() - 1];
        nums2.pop_back();

        size_t concat = std::stoul(std::to_string(second_last) + std::to_string(last));
        nums2.push_back(concat);

        // right side concat *
        if (result % concat == 0 && nums2.size() == 1 && result / concat == nums2[0])
        {
            std::cout << "return at right side concat *\n";
            return true;
        }
        else if (result != concat && result % concat == 0 && nums2.size() > 0)
        {
            std::cout << "recurse at right side concat *\n";
            if (Equation(result, nums2, depth + 1).validate_b())
            {
                return true;
            }
        }

        //  right side concat +
        if (result == concat && nums2.size() == 1)
        {
            std::cout << "return at right side concat +\n";
            return true;
        }
        else if (result >= concat && nums2.size() > 1)
        {
            std::cout << "recurse at right side concat +\n";
            if (Equation(result, nums2, depth + 1).validate_b())
            {
                return true;
            }
        }
    }

    return false;
}
