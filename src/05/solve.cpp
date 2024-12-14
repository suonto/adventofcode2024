#include "05/solve.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <optional>

std::optional<size_t> processUpdate(const std::vector<size_t> &update)
{
    std::unordered_set<size_t> processed;
    for (const auto &page : update)
    {
        if (!)
    }
}

size_t solve(const std::string &input, bool variant_b)
{
    std::istringstream stream(input);
    std::string line;

    // rules map requirer -> vector of prerequisites
    std::unordered_map<size_t, std::vector<size_t>> rules;

    std::vector<std::vector<size_t>> updates;

    while (std::getline(stream, line))
    {
        // rules parsing
        if (line.find('|') != std::string::npos)
        {
            size_t requiree = std::stoi(line.substr(0, 2));
            size_t requirer = std::stoi(line.substr(3, 2));

            if (!rules.contains(requirer))
            {
                rules[requirer] = {};
            }

            rules[requirer].push_back(requiree);
        }

        // update parsing
        else if (line.size() > 0)
        {
            std::stringstream ss(line);
            std::string token;
            std::vector<size_t> update;

            for (size_t i = 0; i < line.size() > 0; i += 3)
            {
                auto sub = line.substr(i, 2);
                update.push_back(std::stoi(sub));
            }

            updates.push_back(update);
        }
    }

    // Print parsed rules
    std::cout << "\nParsed rules:\n";
    for (const auto &pair : rules)
    {
        std::cout << "Requirer " << pair.first << " requires: ";
        for (const auto &requiree : pair.second)
        {
            std::cout << requiree << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nProcessing updates:\n";
    for (const auto &update : updates)
    {
        std::cout << "Update: ";
        for (const auto &u : update)
        {
            std::cout << u << " ";
        }
        std::cout << "\n";
    }

    size_t result = 0;

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
