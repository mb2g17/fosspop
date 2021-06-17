#pragma once

#include <SDL2/SDL.h>

#include "game/obj.hpp"
#include "grid/grid.hpp"

struct Position
{
    int row;
    int col;
};

struct FallingTile
{
    int tile;
    int currentY;
    int X;
    int endingY;
};

class GridObj : public Obj
{
    Grid *grid;
    SDL_Texture *tileTextures[7];

    bool dragging = false;
    int dragRow = -1;
    int dragCol = -1;
    SDL_Texture *dragTex;

    bool falling = false;
    std::vector<FallingTile> *fallingTiles;
    Grid *postFallingGrid;

    SDL_Rect mousePos;

public:
    GridObj(SDL_Renderer *renderer);
    ~GridObj();

    void update(SDL_Renderer *) override;
    void updateMousePos(SDL_Rect);

    void startDrag();
    void endDrag();

    void popCombination(int, int);

private:
    int getMouseRow();
    int getMouseCol();
};