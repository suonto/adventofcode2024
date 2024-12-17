#ifndef EQUATION_H
#define EQUATION_H

#include <vector>
#include <string>

class Equation
{
public:
    Equation(size_t result, const std::vector<size_t> &numbers, size_t depth = 0);

    /**
     * Validates with possible operators.
     * @returns bool valid.
     */
    bool validate() const;
    bool validate_b() const;

    std::string toString() const;

    const size_t result;
    const std::vector<size_t> numbers;
private:
   size_t depth;
};

#endif // EQUATION_H