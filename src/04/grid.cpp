#include "04/grid.h"
#include <string>
#include <iostream>

Grid::Grid() : _grid(std::vector<std::vector<char>>()) {}

void Grid::addRow(std::string input)
{
    std::vector<char> row;
    for (char c : input)
    {
        row.push_back(c);
    }
    _grid.push_back(row);
}
