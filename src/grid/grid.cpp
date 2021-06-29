#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <emscripten.h>

#include "grid/grid.hpp"

Grid::Grid()
{
    // Inits randomness
    this->seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::random_device rd;
    rng = std::mt19937(rd());
    uni = std::uniform_int_distribution<int>(0, 6);
}

Grid::Grid(const Grid &grid)
{
    // Inits randomness
    this->seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::random_device rd;
    rng = std::mt19937(rd());
    uni = std::uniform_int_distribution<int>(0, 6);

    // Inits grid
    for (int row = 0; row < 7; row++)
        for (int col = 0; col < 8; col++)
            this->gridArray[row][col] = grid.gridArray[row][col];

    // Passes over score and moves
    this->score = grid.score;
    this->moves = grid.moves;

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

void Grid::popAllCombinationsAndSpendMove()
{
    // Deduct moves
    this->moves--;
    EM_ASM(setMoves($1), this->moves);

    this->popAllCombinations();
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
    PositionSet fringe = getVeinHere(row, col);
    PositionSet poppingSet;
    auto noOfPoppedTiles = 0;
    auto tile = gridArray[fringe.begin()->row][fringe.begin()->col];

    while (fringe.size() > 0)
    {
        Position poppedPos = *fringe.begin();
        fringe.erase(poppedPos);

        PositionSet combinationTiles = getCombinationHere(poppedPos.row, poppedPos.col);

        for (auto &combinationPos : combinationTiles)
        {
            noOfPoppedTiles++;
            poppingSet.insert(combinationPos);
            fringe.erase(combinationPos);
        }
    }

    // Updates score / moves
    if (tile == 1)
        this->moves += (noOfPoppedTiles - 1);
    else
    {
        auto multiplier = noOfPoppedTiles - 2;
        auto base = (noOfPoppedTiles - 2) * 10;

        std::cout << "Multiplier: " << multiplier << std::endl;
        std::cout << "Base: " << base << std::endl;

        if (tile == 0)
            this->score -= (base * multiplier * 2);
        else
            this->score += (base * multiplier);
    }

    // Update score / moves in web page
    EM_ASM(
        {
            setScore($0);
            setMoves($1);
        },
        this->score, this->moves);

    // Pop all tiles in popping set
    for (auto &poppingPos : poppingSet)
        popTile(poppingPos.row, poppingPos.col);
}

PositionSet Grid::getVeinHere(int row, int col)
{
    int currentType = this->gridArray[row][col];
    PositionSet vein, openPositions, closedPositions;
    openPositions.insert(Position(row, col));

    while (openPositions.size() > 0)
    {
        // Pop element
        Position poppedPosition = *openPositions.begin();
        openPositions.erase(poppedPosition);
        closedPositions.insert(poppedPosition);

        PositionSet neighbours = poppedPosition.getNeighbours();
        for (auto &neighbour : neighbours)
        {
            // Only consider if it's of our type
            int neighbourType = this->gridArray[neighbour.row][neighbour.col];
            if (neighbourType == currentType)
            {
                vein.insert(neighbour);
                if (!closedPositions.contains(neighbour))
                    openPositions.insert(neighbour);
            }
        }
    }

    return vein;
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

PositionSet Grid::getCombinationHere(int row, int col)
{
    int selectedTile = this->gridArray[row][col];
    PositionSet combinationTiles, horizontalTiles, verticalTiles;

    // If empty space, there are no combinations
    if (selectedTile == -1)
        return combinationTiles;

    // LEFT
    for (int i = col; i >= 0; i--)
    {
        if (gridArray[row][i] != selectedTile)
            break;
        else
            horizontalTiles.insert(Position(row, i));
    }

    // RIGHT
    for (int i = col; i <= 7; i++)
    {
        if (gridArray[row][i] != selectedTile)
            break;
        else
            horizontalTiles.insert(Position(row, i));
    }

    if (horizontalTiles.size() >= 3)
    {
        for (auto &pos : horizontalTiles)
            combinationTiles.insert(pos);
    }

    // TOP
    for (int i = row; i >= 0; i--)
    {
        if (gridArray[i][col] != selectedTile)
            break;
        else
            verticalTiles.insert(Position(i, col));
    }

    // BOTTOM
    for (int i = row; i <= 6; i++)
    {
        if (gridArray[i][col] != selectedTile)
            break;
        else
            verticalTiles.insert(Position(i, col));
    }

    if (verticalTiles.size() >= 3)
    {
        for (auto &pos : verticalTiles)
            combinationTiles.insert(pos);
    }

    return combinationTiles;
}

bool Grid::isCombinationHere(int row, int col)
{
    PositionSet combinationHere = getCombinationHere(row, col);
    return combinationHere.size() > 0;
}