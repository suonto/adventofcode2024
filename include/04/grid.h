#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>

class Grid
{
public:
    Grid();
    void addRow(std::string);
    char at(int, int);

private:
    std::vector<std::vector<char>> _grid;
};

#endif // GRID_H