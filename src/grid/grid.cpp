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
    // If we're swapping rows
    if (row1 != row2)
    {
        // If src
        //     V
        //    dst
        if (row2 > row1)
        {
            for (int row = row1; row < row2; row++)
            {
                switchTiles(row, col1, row + 1, col2);
            }
        }

        // If dst
        //     ^
        //    src
        else if (row1 > row2)
        {
            for (int row = row1; row > row2; row--)
            {
                switchTiles(row - 1, col1, row, col2);
            }
        }
    }

    // If we're swapping cols
    else
    {
        // If src --> dst
        if (col2 > col1)
        {
            for (int col = col1; col < col2; col++)
            {
                switchTiles(row1, col, row2, col + 1);
            }
        }

        // If dst <-- src
        else if (col1 > col2)
        {
            for (int col = col1; col > col2; col--)
            {
                switchTiles(row1, col - 1, row2, col);
            }
        }
    }
}

void Grid::switchTiles(int row1, int col1, int row2, int col2)
{
    int oldTile1 = this->getTile(row1, col1);
    int oldTile2 = this->getTile(row2, col2);
    this->gridArray[row1][col1] = oldTile2;
    this->gridArray[row2][col2] = oldTile1;
}

bool Grid::isPositionInvalid(int row, int col)
{
    return col < 0 || col > 8 || row < 0 || row > 7;
}