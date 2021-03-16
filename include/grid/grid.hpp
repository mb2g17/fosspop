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
    void init();
    void init(int[7][8]);
    int getTile(int, int);
    void swap(int, int, int, int);

protected:
    bool isPositionInvalid(int, int);
};