#pragma once

#include <random>

class Grid
{
private:
    // Randomness
    unsigned int seed;
    std::mt19937 rng;
    std::uniform_int_distribution<int> uni;

    bool initialised = false;
    int gridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};

public:
    Grid();
    Grid(const Grid *);

    void init();
    void init(int[7][8]);
    int getTile(int row, int col);

    // SWAPPING
public:
    void swap(int row1, int col1, int row2, int col2);

protected:
    void switchTiles(int row1, int col1, int row2, int col2);

    // POPPING
public:
    void popAllCombinations();
    void popTile(int row, int col);

protected:
    void popCombination(int row, int col);

    // MOVING
public:
    void moveAllTilesDown();

protected:
    void moveTilesDown(int col);

    // FINDING COMBINATIONS
public:
    bool isCombinationAnywhere();

protected:
    bool isCombinationHere(int row, int col);

    // TILE GENERATION
public:
    void fillInSpaces();

protected:
    void setTileRandomly(int row, int col);
    void setTileWithoutMakingCombination(int row, int col);

    // MISCELLANEOUS
protected:
    bool isPositionInvalid(int row, int col);
};