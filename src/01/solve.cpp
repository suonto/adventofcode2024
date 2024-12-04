#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

int solve1(const char *example)
{
    std::istringstream stream(example);
    std::string line;
    std::vector<int> left;
    std::vector<int> right;

    while (std::getline(stream, line))
    {
        std::istringstream lineStream(line);
        int leftValue, rightValue;
        if (lineStream >> leftValue >> rightValue)
        {
            left.push_back(leftValue);
            right.push_back(rightValue);
        }
    }

    // Sort the arrays
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    int result = 0;

    // Print the arrays for demonstration
    std::cout << "Arrays:" << '\n';
    for (int i = 0; i < left.size(); i++)
    {
        const auto diff = abs(left[i] - right[i]);
        result += diff;
        std::cout << left[i] << " " << right[i] << " " << diff << " " << result << '\n';
    }
    std::cout << std::endl;

    return result;
}


int solve2(const char *example)
{
    std::istringstream stream(example);
    std::string line;
    std::vector<int> left;
    std::vector<int> right;

    while (std::getline(stream, line))
    {
        std::istringstream lineStream(line);
        int leftValue, rightValue;
        if (lineStream >> leftValue >> rightValue)
        {
            left.push_back(leftValue);
            right.push_back(rightValue);
        }
    }

    // Sort the arrays
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    int result = 0;

    std::cout << "Solving 2:" << '\n';

    // left and right indexes l and r
    int l = 0;
    int r = 0;

    int val = left[l];

    // left and right multipliers
    int lx = 0;
    int rx = 0;

    // ascend the index of the lower number on sorted lists
    while (l < left.size() || r < right.size()) {
        if (left[l] < val) {
            l++;
            continue;
        }

        if (right[r] < val) {
            r++;
            continue;
        }

        if (left[l] == val) {
            lx++;
            std::cout << "l: " << l << " " << left[l] << " " << lx << '\n';
            l++;
            continue;
        }

        if (right[r] == val) {
            rx++;
            std::cout << "r: " << r << " " << right[r] << " " << rx << '\n';
            r++;
            continue;
        }

        int product = val * lx * rx;
        result += (val * lx * rx);
        std::cout << val << " " << lx << " " << rx << " " << product << " " << result << '\n';
        lx = 0;
        rx = 0;
        if (l == left.size()) {
            break;
        }
        val = left[l];
        std::cout << "new val: " << val << '\n';

    }
    std::cout << std::endl;

    return result;
}