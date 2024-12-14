#ifndef SOLVE_05_H
#define SOLVE_05_H

#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_map>

size_t orderUpdate(std::vector<size_t> update, const std::unordered_map<size_t, std::vector<size_t>> &rules);
size_t solveA(const std::string &s);
size_t solveB(const std::string &s);

#endif // SOLVE_05_H