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
    int getTile(int, int);
    void swap(int, int, int, int);

    void popAllCombinations();
    void popCombination(int, int);
    void popTile(int, int);

    bool isCombinationAnywhere();
    bool isCombinationHere(int, int);

    void setTileRandomly(int, int);
    void setTileWithoutMakingCombination(int, int);

    void moveAllTilesDown();
    void fillInSpaces();

protected:
    void switchTiles(int, int, int, int);
    bool isPositionInvalid(int, int);
    void moveTilesDown(int col);
};