#include <iostream>
#include <random>

#include "grid/grid.hpp"

int Grid::getTile(int row, int col)
{
    // If we're swapping invalid positions
    if (this->isPositionInvalid(row, col))
        throw std::out_of_range("Given positions are not valid");

    return this->gridArray[row][col];
}

void Grid::init()
{
    // Prepares randomness
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, 6);

    for (int row = 0; row < 7; row++)
        for (int col = 0; col < 8; col++)
            this->gridArray[row][col] = uni(rng);

    initialised = true;
}

void Grid::init(int gridArray[7][8])
{
    for (int row = 0; row < 7; row++)
        for (int col = 0; col < 8; col++)
            this->gridArray[row][col] = gridArray[row][col];

    initialised = true;
}

void Grid::swap(int row1, int col1, int row2, int col2)
{
    // If we're swapping diagonally
    if (col1 != col2 && row1 != row2)
        throw std::invalid_argument("Cannot swap diagonally");

    // If we're swapping invalid positions
    if (this->isPositionInvalid(row1, col1) || this->isPositionInvalid(row2, col2))
        throw std::out_of_range("Given positions are not valid");

    // If we're not initialised
    if (!this->initialised)
        throw std::runtime_error("Must be initialised first");

    // Swaps
    int oldTile1 = this->getTile(row1, col1);
    int oldTile2 = this->getTile(row2, col2);
    this->gridArray[row1][col1] = oldTile2;
    this->gridArray[row2][col2] = oldTile1;
}

bool Grid::isPositionInvalid(int row, int col)
{
    return col < 0 || col > 8 || row < 0 || row > 7;
}