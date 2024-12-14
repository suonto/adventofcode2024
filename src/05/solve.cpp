#include "05/solve.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <algorithm>

std::optional<size_t> processUpdate(const std::vector<size_t> &update, const std::unordered_map<size_t, std::vector<size_t>> &rules)
{
    std::unordered_set<size_t> processed;
    std::unordered_set<size_t> remaining(update.begin(), update.end());

    size_t middle_val;

    for (size_t i = 0; i < update.size(); ++i)
    {
        const auto &page = update[i];

        // resolve middle_val
        if (i == (update.size()) / 2)
        {
            middle_val = page;
        }

        auto it = rules.find(page);
        if (it != rules.end())
        {
            // it first is key, second is value
            for (const auto &required : it->second)
            {
                if (!processed.contains(required) && remaining.contains(required))
                {
                    std::cout << "page " << page << " rule " << it->first << " requires " << required << '\n';
                    return std::nullopt;
                }
            }
        }

        processed.insert(page);
        remaining.erase(page);
    }

    return middle_val;
}

size_t orderUpdate(std::vector<size_t> update, const std::unordered_map<size_t, std::vector<size_t>> &rules)
{
    bool zero_swaps = true;

    for (size_t i = 0; i < update.size(); ++i)
    {
        auto it = rules.find(update[i]);

        // while there is a rule for current update[i]
        while (it != rules.end())
        {
            auto rule = it->first;
            auto required_values = it->second;

            std::cout << "at " << i << " (" << update[i] << ") rule " << rule << " with requirements ";
            for (const auto &required : it->second)
            {
                std::cout << required << " ";
            }
            std::cout << '\n';

            bool swapped = false;

            // it first is key, second is value
            for (const auto &required : it->second)
            {

                for (size_t j = i + 1; j < update.size(); j++)
                {
                    if (update[j] == required)
                    {
                        std::cout << "Update " << i << " (" << update[i] << ") requires " << j << " (" << required << ")" << ". Swapping pages." << std::endl;
                        std::swap(update[i], update[j]);
                        std::cout << "Update i after swap " << update[i] << std::endl;
                        swapped = true;
                        zero_swaps = false;
                        break;
                    }
                }

                if (swapped)
                {
                    it = rules.find(update[i]);
                    break;
                }
            }
            if (!swapped)
            {
                break;
            }
        }
    }

    std::cout << "Sorted update: ";
    for (const auto &u : update)
    {
        std::cout << u << " ";
    }
    std::cout << '\n';

    return zero_swaps ? 0 : update[update.size() / 2];
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

    size_t result = 0;

    std::cout << "\nProcessing updates:\n";
    for (const auto &update : updates)
    {
        if (variant_b)
        {
            std::cout << "\nUpdate: ";
            for (const auto &u : update)
            {
                std::cout << u << " ";
            }
            std::cout << '\n';
            auto update_result = orderUpdate(update, rules);
            std::cout << "Update result: " << update_result;
            result += update_result;
        }
        else
        {
            auto update_result = processUpdate(update, rules);
            std::cout << "Update: ";
            for (const auto &u : update)
            {
                std::cout << u << " ";
            }

            if (update_result.has_value())
            {
                std::cout << "result: " << update_result.value();
                result += update_result.value();
            }
            else
            {
                std::cout << " invalid";
            }
        }

        std::cout << "\n";
    }

    std::cout << "\nResult: " << result << std::endl;

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
