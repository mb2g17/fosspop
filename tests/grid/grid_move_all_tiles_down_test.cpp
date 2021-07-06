#include "grid/grid.hpp"
#include "grid_assert.hpp"

#include "gtest/gtest.h"

TEST(GridMoveAllTilesDown, should_move_tiles_on_all_rows_down_scrambled)
{
    int gridArray[7][8] = {
        {0, 1, 0, 3, 4, 1, 6, 3},
        {1, 2, -1, -1, -1, 2, 3, 0},
        {-1, 3, 4, 5, 6, 1, 0, 1},
        {-1, 4, 5, 2, 1, 5, 6, 0},
        {-1, 5, 6, 3, -1, 1, 2, 3},
        {5, 6, 3, 0, -1, -1, -1, 4},
        {-1, -1, -1, 1, -1, 3, 4, 5}};

    auto grid = Grid();
    grid.init(gridArray);
    grid.moveAllTilesDown();

    int expectedGridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, 3},
        {-1, 1, -1, 3, -1, 1, 6, 0},
        {-1, 2, 0, 5, -1, 2, 3, 1},
        {-1, 3, 4, 2, -1, 1, 0, 0},
        {0, 4, 5, 3, 4, 5, 6, 3},
        {1, 5, 6, 0, 6, 1, 2, 4},
        {5, 6, 3, 1, 1, 3, 4, 5}};

    assertGrid(&grid, expectedGridArray);
}

TEST(GridMoveAllTilesDown, should_move_tiles_on_all_rows_down_width_1)
{
    int gridArray[7][8] = {
        {0, 1, 0, 3, 4, 1, 6, 3},
        {1, 2, 1, 4, 5, 2, 3, 0},
        {2, 3, 4, 5, 6, 1, 0, 1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {4, 5, 6, 3, 0, 1, 2, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    auto grid = Grid();
    grid.init(gridArray);
    grid.moveAllTilesDown();

    int expectedGridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 0, 3, 4, 1, 6, 3},
        {1, 2, 1, 4, 5, 2, 3, 0},
        {2, 3, 4, 5, 6, 1, 0, 1},
        {4, 5, 6, 3, 0, 1, 2, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    assertGrid(&grid, expectedGridArray);
}

TEST(GridMoveAllTilesDown, should_move_tiles_on_all_rows_down_width_2)
{
    int gridArray[7][8] = {
        {0, 1, 0, 3, 4, 1, 6, 3},
        {1, 2, 1, 4, 5, 2, 3, 0},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {4, 5, 6, 3, 0, 1, 2, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    auto grid = Grid();
    grid.init(gridArray);
    grid.moveAllTilesDown();

    int expectedGridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 0, 3, 4, 1, 6, 3},
        {1, 2, 1, 4, 5, 2, 3, 0},
        {4, 5, 6, 3, 0, 1, 2, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    assertGrid(&grid, expectedGridArray);
}

TEST(GridMoveAllTilesDown, should_move_tiles_on_all_rows_down_width_3)
{
    int gridArray[7][8] = {
        {0, 1, 0, 3, 4, 1, 6, 3},
        {1, 2, 1, 4, 5, 2, 3, 0},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    auto grid = Grid();
    grid.init(gridArray);
    grid.moveAllTilesDown();

    int expectedGridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 0, 3, 4, 1, 6, 3},
        {1, 2, 1, 4, 5, 2, 3, 0},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    assertGrid(&grid, expectedGridArray);
}

TEST(GridMoveAllTilesDown, should_move_tiles_on_all_rows_down_width_4)
{
    int gridArray[7][8] = {
        {0, 1, 0, 3, 4, 1, 6, 3},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    auto grid = Grid();
    grid.init(gridArray);
    grid.moveAllTilesDown();

    int expectedGridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 0, 3, 4, 1, 6, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    assertGrid(&grid, expectedGridArray);
}

TEST(GridMoveAllTilesDown, should_move_tiles_on_all_rows_down_width_5)
{
    int gridArray[7][8] = {
        {0, 1, 0, 3, 4, 1, 6, 3},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    auto grid = Grid();
    grid.init(gridArray);
    grid.moveAllTilesDown();

    int expectedGridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 0, 3, 4, 1, 6, 3},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    assertGrid(&grid, expectedGridArray);
}

TEST(GridMoveAllTilesDown, should_move_tiles_on_all_rows_down_width_6)
{
    int gridArray[7][8] = {
        {0, 1, 0, 3, 4, 1, 6, 3},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};

    auto grid = Grid();
    grid.init(gridArray);
    grid.moveAllTilesDown();

    int expectedGridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 1, 0, 3, 4, 1, 6, 3}};

    assertGrid(&grid, expectedGridArray);
}