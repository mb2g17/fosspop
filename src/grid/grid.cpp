#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>

#include "grid/grid.hpp"

Grid::Grid()
{
}

Grid::Grid(const Grid *grid)
{
    for (int row = 0; row < 7; row++)
        for (int col = 0; col < 8; col++)
            this->gridArray[row][col] = grid->gridArray[row][col];

    initialised = true;
}

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

    std::cout << "Switched tiles" << std::endl;
}

void Grid::popTile(int row, int col)
{
    // Pops tile
    this->gridArray[row][col] = -1;

    // Moves all tiles down
    for (int i = row; i > 0; i--)
    {
        this->gridArray[i][col] = this->gridArray[i - 1][col];
    }

    // Select random new tile at the top, such that it won't make a combination
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, 6);

    this->gridArray[0][col] = uni(rng);
    this->setTileWithoutMakingCombination(0, col);
}

void Grid::setTileWithoutMakingCombination(int row, int col)
{
    // Shuffle tiles
    std::array<int, 6> tiles{1, 2, 3, 4, 5, 6};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(tiles.begin(), tiles.end(), std::default_random_engine(seed));
    for (int &tile : tiles)
    {
        this->gridArray[0][col] = tile;
        if (!this->isCombinationHere(0, col))
            break;
    }
}

bool Grid::isPositionInvalid(int row, int col)
{
    return col < 0 || col > 8 || row < 0 || row > 7;
}

bool Grid::isCombinationHere(int row, int col)
{
    // Get current tile
    auto thisTile = gridArray[row][col];

    // Remembers how many same-time neighbours there are
    int noOfSameTileNeighbours = 0;

    // Checks left side
    for (int i = col; i >= 0; i--)
    {
        if (gridArray[row][i] != thisTile)
            break;
        else
            noOfSameTileNeighbours++;
    }

    // Checks right side
    for (int i = col; i <= 7; i++)
    {
        if (gridArray[row][i] != thisTile)
            break;
        else
            noOfSameTileNeighbours++;
    }

    // Checks top side
    for (int i = row; i >= 0; i--)
    {
        if (gridArray[i][col] != thisTile)
            break;
        else
            noOfSameTileNeighbours++;
    }

    // Checks bottom side
    for (int i = row; i <= 6; i++)
    {
        if (gridArray[i][col] != thisTile)
            break;
        else
            noOfSameTileNeighbours++;
    }

    // Offset
    noOfSameTileNeighbours -= 4;

    std::cout << "Number of same tile neighbours: " << noOfSameTileNeighbours << std::endl;

    return noOfSameTileNeighbours >= 2;
}