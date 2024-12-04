#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

int solve(const char *example)
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