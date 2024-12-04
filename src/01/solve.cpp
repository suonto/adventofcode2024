#include <iostream>
#include <cstdint>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

uint8_t solve(const char *example)
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

    // Print the arrays for demonstration
    std::cout << "Arrays:" << std::endl;
    for (int i; i < left.size(); i++)
    {
        std::cout << left[i] << " " << right[i] << std::endl;
    }
    std::cout << std::endl;

    return 0;
}