#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "grid/grid_obj.hpp"
#include "assets/textures.hpp"

GridObj::GridObj(SDL_Renderer *renderer)
{
    // Initialises grid
    this->grid = new Grid();
    this->grid->init();

    // Initialises other stuff
    this->fallingTiles = new std::vector<FallingTile>();
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

            // If invalid tile, do not render
            if (grid->getTile(row, col) == -1)
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
            auto tileTex = Textures::getInstance().getTileTexture(i);
            SDL_RenderCopy(renderer, tileTex, NULL, &pos);
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

    // Falling logic
    if (this->falling)
    {
        auto thereExistsMovingTiles = false;

        // For every falling tile
        for (auto iter = fallingTiles->begin(); iter != fallingTiles->end(); ++iter)
        {
            // Gets tile
            auto tile = *iter;

            // Draws tile
            auto tileTexture = Textures::getInstance().getTileTexture(tile.tile);
            auto pos = SDL_Rect{.x = tile.X, .y = (int)tile.currentY, .w = 64, .h = 64};
            SDL_RenderCopy(renderer, tileTexture, NULL, &pos);

            // Move tile, if it should be moved
            if (tile.currentY < tile.endingY)
            {
                iter->currentY += iter->velocity;
                iter->velocity += iter->accel;
                thereExistsMovingTiles = true;
            }

            // If tile has gone far enough, flag it for deletion
            if (tile.currentY >= tile.endingY)
                tile.currentY = tile.endingY;
        }

        // If there are no more falling tiles
        if (!thereExistsMovingTiles)
        {
            falling = false;
            fallingTiles->clear();

            // Swap grid to post falling grid
            delete this->grid;
            this->grid = this->postFallingGrid;

            // If there's still combinations, continue animation
            if (this->grid->isCombinationAnywhere())
            {
                this->grid->popAllCombinations();
                this->animate();
            }
        }
    }
}

void GridObj::updateMousePos(SDL_Rect mousePos)
{
    this->mousePos = mousePos;
}

void GridObj::startDrag()
{
    // If things are falling, don't start any drag
    if (falling)
        return;

    auto row = getMouseRow();
    auto col = getMouseCol();

    this->dragging = true;
    this->dragRow = row;
    this->dragCol = col;

    auto tile = this->grid->getTile(row, col);
    auto tileTexture = Textures::getInstance().getTileTexture(tile);
    this->dragTex = tileTexture;
    std::cout << "Row: " << row << ", Col: " << col << std::endl;
}

void GridObj::endDrag()
{
    // If things are falling, don't do any drag
    if (falling)
        return;

    auto startRow = dragRow;
    auto startCol = dragCol;
    auto endRow = getMouseRow();
    auto endCol = getMouseCol();
    this->dragging = false;

    auto isNotDiagonal = startRow == endRow || startCol == endCol;
    if (isNotDiagonal)
    {
        bool willMakeCombination = false;

        Grid *checkGrid = new Grid(*this->grid);
        checkGrid->swap(startRow, startCol, endRow, endCol);
        willMakeCombination = checkGrid->isCombinationAnywhere();

        delete checkGrid;
        checkGrid = NULL;

        if (willMakeCombination)
        {
            grid->swap(startRow, startCol, endRow, endCol);

            // Pop all made combinations
            this->grid->popAllCombinations();
            this->animate();
        }
    }
}

void GridObj::animate()
{
    // Sets up alt grid, to help animate new tiles
    Grid *altGrid = new Grid(*this->grid);
    altGrid->moveAllTilesDown();

    // Sets up post falling grid
    this->postFallingGrid = new Grid(*this->grid);
    this->postFallingGrid->moveAllTilesDown();
    this->postFallingGrid->fillInSpaces();

    // Add items for falling animation OF OLD TILES
    for (auto col = 0; col < 8; col++)
    {
        auto startFalling = false;
        auto noOfSpaces = 0;

        for (auto row = 6; row >= 0; row--)
        {
            if (this->grid->getTile(row, col) == -1)
            {
                noOfSpaces++;

                if (!startFalling)
                    startFalling = true;
            }

            // If this pos is falling, and there's a tile in the main grid
            if (this->grid->getTile(row, col) > -1 && startFalling)
            {
                // Creates animation for this tile
                auto tileNumber = this->grid->getTile(row, col);

                falling = true;
                FallingTile tile = FallingTile{
                    .tile = tileNumber,
                    .X = 50 + 70 * col,
                    .currentY = (float)(50 + 70 * row),
                    .endingY = 50 + 70 * (row + noOfSpaces),
                    .velocity = 0,
                    .accel = 0.5f};
                fallingTiles->push_back(tile);

                // Removes it from actual graph
                this->grid->popTile(row, col);
            }
        }
    }

    // Add items for falling animations of NEW TILES
    for (auto col = 0; col < 8; col++)
    {
        // Gets number of top spaces
        auto noOfTopSpaces = 0;
        for (auto row = 0; row <= 6; row++)
        {
            if (altGrid->getTile(row, col) == -1)
                noOfTopSpaces++;
        }

        // If there are no top spaces, then move on
        if (noOfTopSpaces == 0)
            continue;

        // Create animations for new tiles in those top spots
        for (auto row = 0; row <= 6; row++)
        {
            auto tileNumberNormalGrid = altGrid->getTile(row, col);
            auto tileNumberPostGrid = this->postFallingGrid->getTile(row, col);

            if (tileNumberNormalGrid == -1)
            {
                falling = true;
                FallingTile tile = FallingTile{
                    .tile = tileNumberPostGrid,
                    .X = 50 + 70 * col,
                    .currentY = (float)(50 - 70 * (noOfTopSpaces - row)),
                    .endingY = 50 + 70 * row,
                    .velocity = 0,
                    .accel = 0.5f};
                fallingTiles->push_back(tile);
            }
            else
                break;
        }
    }
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