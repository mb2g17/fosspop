#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "grid/grid.hpp"
#include "assets/audio.hpp"

Grid::Grid()
{
    random = Random();
}

Grid::Grid(const Grid &grid)
{
    random = Random();

    // Inits grid
    for (int row = 0; row < 7; row++)
        for (int col = 0; col < 8; col++)
            this->gridArray[row][col] = grid.gridArray[row][col];

    // Passes over score and moves
    this->props = grid.props;

    initialised = true;
}

int Grid::getTile(int row, int col)
{
    // If we're swapping invalid positions
    if (this->isPositionInvalid(row, col))
        throw std::out_of_range("Given positions are not valid");

    return this->gridArray[row][col];
}

Properties &Grid::getProps()
{
    return props;
}

void Grid::init()
{
    // Randomly inits grid
    for (int row = 0; row < 7; row++)
        for (int col = 0; col < 8; col++)
            this->setTileRandomly(row, col);

    // Removes combinations (temporarily locks properties so score doesn't change)
    this->props.lockProperties();
    if (this->isCombinationAnywhere())
    {
        this->popAllCombinations();
        this->fillInSpaces();
    }
    this->props.unlockProperties();

    initialised = true;
}

void Grid::init(int gridArray[7][8])
{
    for (int row = 0; row < 7; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            auto tile = gridArray[row][col];
            if (tile < -1 || tile > 6)
                throw std::out_of_range("Tile in array is out of range!");

            this->gridArray[row][col] = tile;
        }
    }

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
    this->props.subtractMoves(1);
#ifdef __EMSCRIPTEN__
    EM_ASM(setMoves($1), this->props.getMoves());
#endif

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

    // Remembers if we're at max multiplier
    auto atMaxMultiplierBefore = this->props.getMultiplier() == 10;

    // Updates score / moves
    if (tile == 1)
        this->props.addMoves(noOfPoppedTiles - 1);
    else
    {
        auto multiplier = noOfPoppedTiles - 2;
        auto base = (noOfPoppedTiles - 2) * 10;

        if (tile == 0) // Broken heart
            this->props.subtractScore(base * multiplier * 2);
        else if (tile == 2) // Multiplier
            this->props.addMultiplier(multiplier);
        else
            this->props.addScore(base * multiplier * props.getMultiplier());
    }

    // Play sound depending on vein (only if we've finished initialising)
    if (initialised)
    {
        if (tile == 0)
            Audio::getInstance().playNegative();
        else if (tile == 1)
            Audio::getInstance().playRing();
        else if (tile == 2)
        {
            if (atMaxMultiplierBefore)
                Audio::getInstance().playMaxPink();
            else
            {
                // If we've just made it to max multiplier
                if (this->props.getMultiplier() == 10)
                    Audio::getInstance().playMaxMultiplier();
                else
                    Audio::getInstance().playPink();
            }
        }
        else
        {
            if (noOfPoppedTiles == 3)
                Audio::getInstance().playPositive();
            else
                Audio::getInstance().playMorePositive();
        }
    }

    // Update score / moves in web page
#ifdef __EMSCRIPTEN__
    EM_ASM(
        {
            setScore($0);
            setMoves($1);
            setMultiplier($2);
        },
        props.getScore(), props.getMoves(), props.getMultiplier());
#endif

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
    if (row < 0)
        throw std::out_of_range("Row is too low");
    if (row >= 7)
        throw std::out_of_range("Row is too high");
    if (col < 0)
        throw std::out_of_range("Col is too low");
    if (col >= 8)
        throw std::out_of_range("Col is too high");

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
    int noOfBrokenHearts = findNumberOfBrokenHearts();
    int generatedTile = random.getRandomTile();

    if (noOfBrokenHearts >= 12)
        while (generatedTile == 0)
            generatedTile = random.getRandomTile();

    this->gridArray[row][col] = generatedTile;
}

void Grid::setTileWithoutMakingCombination(int row, int col)
{
    // Shuffle tiles
    std::array<int, 7> tiles{0, 1, 2, 3, 4, 5, 6};
    shuffle(tiles.begin(), tiles.end(), std::default_random_engine(random.getSeed()));

    int noOfBrokenHearts = findNumberOfBrokenHearts();
    for (int &tile : tiles)
    {
        if (tile == 0 && noOfBrokenHearts >= 12)
            continue;

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

int Grid::findNumberOfBrokenHearts()
{
    int count = 0;

    for (auto row = 0; row < 7; row++)
        for (auto col = 0; col < 8; col++)
            if (gridArray[row][col] == 0)
                count++;

    return count;
}