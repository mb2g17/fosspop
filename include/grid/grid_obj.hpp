#pragma once

#include <SDL2/SDL.h>

#include "game/obj.hpp"
#include "grid/grid.hpp"

struct FallingTile
{
    int tile;
    int X;
    float currentY;
    int endingY;
    float velocity;
    float accel;
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

private:
    void animate();
    int getMouseRow();
    int getMouseCol();
};