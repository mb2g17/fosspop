#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>

#include "grid/grid.hpp"

Grid::Grid()
{
    // Inits randomness
    this->seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::random_device rd;
    rng = std::mt19937(rd());
    uni = std::uniform_int_distribution<int>(0, 6);
}

Grid::Grid(const Grid *grid)
{
    // Inits randomness
    this->seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::random_device rd;
    rng = std::mt19937(rd());
    uni = std::uniform_int_distribution<int>(0, 6);

    // Inits grid
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
    // Randomly inits grid
    for (int row = 0; row < 7; row++)
        for (int col = 0; col < 8; col++)
            this->setTileRandomly(row, col);

    // Removes combinations
    if (this->isCombinationAnywhere())
    {
        this->popAllCombinations();
        this->fillInSpaces();
    }

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

void Grid::popAllCombinations()
{
    for (auto row = 0; row < 7; row++)
        for (auto col = 0; col < 8; col++)
            if (this->isCombinationHere(row, col))
                this->popCombination(row, col);
}

void Grid::popCombination(int row, int col)
{
    // STEP 1: collect set of all tiles in vein
    // STEP 2: pick arbitrary tile, remove from fringe
    // STEP 3: check if >3 horizontally or vertically
    // STEP 4: flag tiles to 'pop' in a popping set, remove from fringe
    // STEP 5: if fringe is non-empty, repeat from step 2

    // Get tile type we need to pop
    int tileType = this->getTile(row, col);

    this->popTile(row, col);

    // Pop above (if we're not already at the top)
    if (row > 0)
    {
        for (int i = row - 1; i >= 0; i--)
            if (this->getTile(i, col) == tileType)
                this->popTile(i, col);
            else
                break;
    }

    // Pop below (if we're not already at the bottom)
    if (row < 6)
    {
        for (int i = row + 1; i <= 6; i++)
            if (this->getTile(i, col) == tileType)
                this->popTile(i, col);
            else
                break;
    }

    // Pop left (if we're not already at the far left)
    if (col > 0)
    {
        for (int i = col - 1; i >= 0; i--)
            if (this->getTile(row, i) == tileType)
                this->popTile(row, i);
            else
                break;
    }

    // Pop right (if we're not already at the far right)
    if (col < 7)
    {
        for (int i = col + 1; i <= 7; i++)
            if (this->getTile(row, i) == tileType)
                this->popTile(row, i);
            else
                break;
    }
}

void Grid::popTile(int row, int col)
{
    this->gridArray[row][col] = -1;
}

void Grid::moveAllTilesDown()
{
    for (int col = 0; col < 8; col++)
        this->moveTilesDown(col);
}

void Grid::moveTilesDown(int col)
{
    bool moved = true;

    while (moved)
    {
        moved = false;
        for (int i = 0; i < 6; i++)
        {
            // If this IS an empty space, do nothing
            if (this->gridArray[i][col] == -1)
                continue;

            // If there's an empty space right beneath, take its place (fall)
            if (this->gridArray[i + 1][col] == -1)
            {
                this->gridArray[i + 1][col] = this->gridArray[i][col];
                this->gridArray[i][col] = -1;
                moved = true;
            }
        }
    }
}

void Grid::setTileRandomly(int row, int col)
{
    this->gridArray[row][col] = uni(rng);
}

void Grid::setTileWithoutMakingCombination(int row, int col)
{
    // Shuffle tiles
    std::array<int, 7> tiles{0, 1, 2, 3, 4, 5, 6};
    shuffle(tiles.begin(), tiles.end(), std::default_random_engine(this->seed));
    this->seed++;

    for (int &tile : tiles)
    {
        this->gridArray[row][col] = tile;
        if (!this->isCombinationAnywhere())
            break;
    }
}

void Grid::fillInSpaces()
{
    for (auto row = 0; row < 7; row++)
    {
        for (auto col = 0; col < 8; col++)
        {
            if (this->gridArray[row][col] == -1)
                this->setTileWithoutMakingCombination(row, col);
        }
    }
}

bool Grid::isPositionInvalid(int row, int col)
{
    return col < 0 || col > 8 || row < 0 || row > 7;
}

bool Grid::isCombinationAnywhere()
{
    for (auto row = 0; row < 7; row++)
        for (auto col = 0; col < 8; col++)
            if (this->isCombinationHere(row, col))
                return true;
    return false;
}

bool Grid::isCombinationHere(int row, int col)
{
    // Get current tile
    auto thisTile = gridArray[row][col];

    // If this is an empty space, then it isn't a combination
    if (thisTile == -1)
        return false;

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

    //std::cout << "Number of same tile neighbours: " << noOfSameTileNeighbours << std::endl;

    return noOfSameTileNeighbours >= 2;
}