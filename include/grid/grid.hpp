#pragma once

#include "grid/position.hpp"
#include "grid/properties.hpp"
#include "grid/random.hpp"

#include <random>

class Grid
{
private:
    bool initialised = false;
    int gridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};

    Random random;
    Properties props;

public:
    Grid();
    Grid(const Grid &);

    void init();
    void init(int[7][8]);
    int getTile(int row, int col);
    Properties &getProps();

    // SWAPPING
public:
    void swap(int row1, int col1, int row2, int col2);

protected:
    void switchTiles(int row1, int col1, int row2, int col2);

    // POPPING
public:
    void popAllCombinationsAndSpendMove();
    void popAllCombinations();
    void popTile(int row, int col);

protected:
    void popCombination(int row, int col);
    PositionSet getVeinHere(int row, int col);

    // MOVING
public:
    void moveAllTilesDown();

protected:
    void moveTilesDown(int col);

    // FINDING COMBINATIONS
public:
    bool isCombinationAnywhere();

protected:
    PositionSet getCombinationHere(int row, int col);
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
    int findNumberOfBrokenHearts();
};