#include "grid/grid.hpp"

#include "gtest/gtest.h"

TEST(GridFillInSpaces, should_fill_empty_spaces)
{
    int gridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};
    auto grid = Grid();
    grid.init(gridArray);
    grid.fillInSpaces();

    for (auto row = 0; row < 7; row++)
        for (auto col = 0; col < 8; col++)
            EXPECT_GE(grid.getTile(row, col), 0);
}

TEST(GridFillInSpaces, should_not_affect_nonempty_tiles)
{
    int gridArray[7][8] = {
        {0, 1, 2, 3, 4, 5, 6, 3},
        {1, 2, 3, 4, 5, 6, 3, 0},
        {2, 3, 1, 5, 6, 3, 0, 1},
        {3, 4, 5, 6, 3, 0, 1, 2},
        {4, 5, 6, 3, 0, 1, 2, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 2, 4, 5}};
    auto grid = Grid();
    grid.init(gridArray);
    grid.fillInSpaces();

    for (auto row = 0; row < 7; row++)
        for (auto col = 0; col < 8; col++)
            EXPECT_EQ(grid.getTile(row, col), gridArray[row][col]);
}