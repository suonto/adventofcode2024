#ifndef SOLVE_06_H
#define SOLVE_06_H

#include "directions.h"
#include "pos.h"

#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_set>

/**
 * Path step at position pos.
 * Direction in an out are different if step is a turn.
 */
struct Step
{
    GridPos pos;
    CardinalDirection dir_in;
    CardinalDirection dir_out;

    Step(const GridPos &p, const CardinalDirection &in, const CardinalDirection &out)
        : pos(p), dir_in(in), dir_out(out) {}
};

struct Path
{
    std::vector<Step> steps;
    std::unordered_set<GridPos> positions;

    Path() : steps({}), positions({}) {}

    void addStep(const Step &step)
    {
        positions.insert(step.pos);
        steps.push_back(step);
    }
};

enum class Intention
{
    Advance,
    Turn,
    Exit
};

size_t solveA(const std::string &s);
size_t solveB(const std::string &s);

#endif // SOLVE_06_H