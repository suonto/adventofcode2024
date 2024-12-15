#include "grid.h"
#include "pos.h"
#include "directions.h"
#include "06/solve.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <optional>
#include <unordered_set>

/**
 * find path steps at pos or nullopt.
 */
std::optional<std::vector<Step>> findSteps(const Path &path, const GridPos &pos)
{
    std::vector<Step> result;
    // optimization O(1)
    if (!path.positions.contains(pos))
    {
        return std::nullopt;
    }

    // Check vector elements
    for (const Step &path_step : path.steps)
    {
        if (path_step.pos == pos)
        {
            result.push_back(path_step);
        }
    }

    if (result.size() == 0)
    {
        throw std::logic_error("No step found by pos");
    }

    return result;
}

/**
 * Path contains a step with equal out direction.
 */
bool containsStep(const Path &path, const Step &step)
{
    // optimization O(1)
    if (!path.positions.contains(step.pos))
    {
        return false;
    }

    // Check vector elements
    for (const Step &path_step : path.steps)
    {
        if (path_step.pos == step.pos && path_step.dir_out == step.dir_out)
        {
            return true;
        }
    }

    return false;
}

/**
 * Given current pos and heading, look forward
 * @return the intention
 */
Intention getIntention(Grid<char> &grid, const GridPos &pos, const CardinalDirection &dir)
{
    // See what's in front of the current position
    auto maybe_next_pos = grid.getPos(pos, dir);

    if (!maybe_next_pos.has_value())
    {
        return Intention::Exit;
    }

    auto next_val = grid.at(maybe_next_pos.value());

    if (next_val == '#')
    {
        return Intention::Turn;
    }
    return Intention::Advance;
}

/**
 * @return 1 if the dream results in a loop else 0.
 * @param param path is an imaginary path, where the real path last step is a turn right.
 *
 * While in imagination:
 * Check if walking would (eventually) create a loop.
 *  - keep tracking the imaginary guard path.
 *  - a loop is formed if at any point pos and heading match a step in path
 */
size_t dreamWalk(Grid<char> &grid, Path path, GridPos pos, CardinalDirection heading)
{
    while (true)
    {
        Intention intent = getIntention(grid, pos, heading);

        auto dir_in = path.steps.size() ? path.steps[path.steps.size() - 1].dir_out : CardinalDirection::North;

        // Exit if void is due
        if (intent == Intention::Exit)
        {
            return 0;
        }

        if (intent == Intention::Turn)
        {
            heading = next(heading);
            continue;
        }

        auto new_step = Step(pos, dir_in, heading);

        if (containsStep(path, new_step))
        {
            auto loop_pos = grid.getPos(pos, dir_in);
            if (!loop_pos)
            {
                throw std::logic_error("No loop pos");
            }
            auto o_pos = loop_pos.value();
            std::cout << "loop at step " << new_step.pos.toString() << " " << toString(new_step.dir_in) << " " << o_pos.toString() << '\n';
            for (size_t y = 0; y < grid.ySize(); y++)
            {
                for (size_t x = 0; x < grid.xSize(y); x++)
                {
                    GridPos p(y, x);
                    auto cell = grid.at(p);
                    auto path_steps = findSteps(path, p);
                    if (o_pos == p)
                    {
                        std::cout << 'O';
                    }
                    else if (path_steps.has_value())
                    {
                        auto p_steps = path_steps.value();

                        if (cell == '^')
                        {
                            std::cout << '^';
                        }
                        else if (p_steps.size() > 1 || p_steps[0].dir_in != p_steps[0].dir_out)
                        {
                            std::cout << '+';
                        }
                        else if (p_steps[0].dir_in == CardinalDirection::North || p_steps[0].dir_in == CardinalDirection::South)
                        {
                            std::cout << '|';
                        }
                        else
                        {
                            std::cout << '-';
                        }
                    }
                    else
                    {
                        std::cout << cell;
                    }
                }
                std::cout << '\n';
            }
            return 1;
        }
        path.addStep(new_step);

        auto pos_maybe = grid.getPos(pos, heading);
        if (!pos_maybe.has_value())
        {
            throw std::logic_error("No next pos while dream walking");
        }
        pos = pos_maybe.value();
    }

    throw std::logic_error("Dream walk doesn't exit naturally");
}

/**
 * Guard walks until exits grid.
 *
 * @param pos is initially a copy of
 *
 * if B, every time the next step is forward:
 *   - before taking the step,
 *     dream a littel dream of it walking right instead
 *     (except if next is start or exit)
 *   - if the dream results in a loop, increment result
 *   - finally take the step forward
 *
 * @return for A unique path tiles, for B the number of dreamed loops.
 */
size_t walk(Grid<char> &grid, const GridPos &start, bool variant_b)
{
    Path path;
    GridPos pos = start;
    CardinalDirection heading = CardinalDirection::North;

    size_t result = 0;

    while (true)
    {
        char &valRef = grid.getValRef(pos);
        if (!variant_b && valRef != 'X')
        {
            valRef = 'X';
            result++;
        }

        Intention intent = getIntention(grid, pos, heading);

        auto dir_in = path.steps.size() ? path.steps[path.steps.size() - 1].dir_out : CardinalDirection::North;

        // Exit if void is due
        if (intent == Intention::Exit)
        {
            std::cout << "Guard exit at " << pos.toString() << '\n';
            path.addStep(Step(pos, dir_in, heading));
            break;
        }

        // if # in front, turn without walking
        if (intent == Intention::Turn)
        {
            heading = next(heading);
            continue;
        }

        // Step to be added is walking forward, which increments position
        // before incrementing position, dream a turn and dream walk
        if (variant_b)
        {
            result += dreamWalk(grid, path, pos, next(heading));
        }

        // Actually moving
        path.addStep(Step(pos, dir_in, heading));
        auto pos_maybe = grid.getPos(pos, heading);
        if (!pos_maybe.has_value())
        {
            throw std::logic_error("No next pos while walking");
        }
        pos = pos_maybe.value();
    }

    if (!variant_b)
    {
        std::cout << grid.toString() << '\n';
    }

    return result;
}

size_t solve(const std::string &example, bool variant_b)
{
    std::istringstream stream(example);
    std::string line;
    size_t result = 0;

    Grid<char> grid;

    std::cout << '\n';
    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            continue;
        };
        std::vector<char> row;
        for (char c : line)
        {
            row.push_back(c);
        }

        grid.addRow(row);
        std::cout << line << '\n';
    }

    std::cout << '\n'
              << "Trying grid cells" << '\n';

    GridPos start(0, 0);
    CardinalDirection guard_dir = CardinalDirection::North;

    for (size_t y = 0; y < grid.ySize(); y++)
    {
        for (size_t x = 0; x < grid.xSize(y); x++)
        {
            GridPos current(y, x);

            if (grid.at(current) == '^')
            {
                start = current;
                std::cout << "Guard start " << toString(guard_dir) << " at " << current.toString() << '\n';
                break;
            }
            if (start == current)
            {
                break;
            }
        }
    }

    GridPos guard_pos = start;

    if (!variant_b)
    {
        result = walk(grid, start, false);
    }
    else
    {
        result = walk(grid, start, true);
    }

    std::cout << "Result " << result << std::endl;

    return result;
}

size_t solveA(const std::string &example)
{
    return solve(example, false);
}

size_t solveB(const std::string &example)
{
    return solve(example, true);
}
