#pragma once

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

public:
    Grid();
    Grid(const Grid *);

    void init();
    void init(int[7][8]);
    int getTile(int, int);
    void swap(int, int, int, int);

    bool isCombinationHere(int, int);

protected:
    void switchTiles(int, int, int, int);
    bool isPositionInvalid(int, int);
};