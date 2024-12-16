#ifndef EQUATION_H
#define EQUATION_H

#include <vector>
#include <string>

class Equation
{
public:
    Equation(size_t result, const std::vector<size_t> &numbers);

    /**
     * Validates with possible operators.
     * @returns the number of valid combinations.
     */
    size_t validate() const;

    std::string toString() const;

    const size_t result;
    const std::vector<size_t> numbers;
};

#endif // EQUATION_H