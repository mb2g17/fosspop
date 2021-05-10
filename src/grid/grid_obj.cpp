#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "grid/grid_obj.hpp"

GridObj::GridObj(SDL_Renderer *renderer)
{
    // Initialises textures
    const char *filenames[7] = {
        "assets/blue.fw.png",
        "assets/green.fw.png",
        "assets/orange.fw.png",
        "assets/pink.fw.png",
        "assets/purple.fw.png",
        "assets/red.fw.png",
        "assets/yellow.fw.png"};

    for (auto i = 0; i < 7; i++)
    {
        SDL_Surface *image = IMG_Load(filenames[i]);
        this->tileTextures[i] = SDL_CreateTextureFromSurface(renderer, image);
    }

    // Initialises grid
    this->grid = new Grid();
    this->grid->init();
}

void GridObj::update(SDL_Renderer *renderer)
{
    // Draws grid
    for (int row = 0; row < 7; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            // If dragging tile, do not render
            if (dragging && row == dragRow && col == dragCol)
                continue;

            // Get this tile's texture ID
            int i = grid->getTile(row, col);

            // Position of this tile
            auto x = 70 * col + this->getX();
            auto y = 70 * row + this->getY();

            // Offset it, depending on dragging
            if (dragging)
            {
                auto currentRow = getMouseRow();
                auto currentCol = getMouseCol();

                // If we should shift this left
                if (dragRow == row && currentRow == row &&
                    dragCol < col && currentCol >= col)
                    x -= 70;

                // If we should shift this right
                if (dragRow == row && currentRow == row &&
                    dragCol > col && currentCol <= col)
                    x += 70;

                // If we should shift this up
                if (dragCol == col && currentCol == col &&
                    dragRow < row && currentRow >= row)
                    y -= 70;

                // If we should shift this down
                if (dragCol == col && currentCol == col &&
                    dragRow > row && currentRow <= row)
                    y += 70;
            }

            // Set position
            SDL_Rect pos{
                .x = x,
                .y = y,
                .w = 64,
                .h = 64};

            // Draw this tile
            SDL_RenderCopy(renderer, this->tileTextures[i], NULL, &pos);
        }
    }

    // Dragging logic if we're dragging
    if (this->dragging)
    {
        // Draws dragging tile
        SDL_Rect dragPos{
            .x = this->mousePos.x - 32,
            .y = this->mousePos.y - 32,
            .w = 64,
            .h = 64};
        SDL_RenderCopy(renderer, this->dragTex, NULL, &dragPos);
    }
}

void GridObj::updateMousePos(SDL_Rect mousePos)
{
    this->mousePos = mousePos;
}

void GridObj::startDrag()
{
    auto row = getMouseRow();
    auto col = getMouseCol();

    this->dragging = true;
    this->dragRow = row;
    this->dragCol = col;

    auto tile = this->grid->getTile(row, col);
    this->dragTex = tileTextures[tile];
    std::cout << "Row: " << row << ", Col: " << col << std::endl;
}

void GridObj::endDrag()
{
    auto startRow = dragRow;
    auto startCol = dragCol;
    auto endRow = getMouseRow();
    auto endCol = getMouseCol();
    this->dragging = false;

    grid->swap(startRow, startCol, endRow, endCol);
}

int GridObj::getMouseRow()
{
    auto row = (mousePos.y - getY()) / 70;
    return row;
}

int GridObj::getMouseCol()
{
    auto col = (mousePos.x - getX()) / 70;
    return col;
}