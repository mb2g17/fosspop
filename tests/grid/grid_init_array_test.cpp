#include "grid/grid.hpp"

#include "gtest/gtest.h"

TEST(GridInitArray, should_fill_in_values_from_array_into_grid)
{
    Grid grid;
    int gridArray[7][8] = {
        {0, 1, -1, 3, 4, -1, 6, 3},
        {1, 2, -1, 4, 5, -1, 3, 0},
        {2, 3, 4, 5, 6, -1, 0, 1},
        {3, 4, 5, 6, 3, 0, 1, 2},
        {4, 5, 6, 3, 0, 1, 2, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    grid.init(gridArray);

    for (auto row = 0; row < 7; row++)
        for (auto col = 0; col < 8; col++)
            EXPECT_EQ(grid.getTile(row, col), gridArray[row][col]);
}

TEST(GridInitArray, should_not_allow_values_too_low)
{
    Grid grid;
    int gridArray[7][8] = {
        {0, 1, 2, 3, 4, 5, 6, 3},
        {1, 2, 3, -4, 5, 6, 3, 0},
        {-2, 3, 4, 5, 6, 3, 0, 1},
        {3, 4, 5, 6, -3, 0, 1, 2},
        {4, 5, -6, 3, 0, 1, 2, 3},
        {-5, -6, -3, 0, 1, -2, -3, -4},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    EXPECT_THROW(grid.init(gridArray), std::out_of_range);
}

TEST(GridInitArray, should_not_allow_values_too_high)
{
    Grid grid;
    int gridArray[7][8] = {
        {0, 1, 2, 3, 4, 5, 6, 7},
        {1, 2, 3, 4, 5, 6, 7, 0},
        {2, 3, 8, 5, 6, 7, 0, 1},
        {3, 4, 5, 6, 7, 0, 1, 2},
        {4, 5, 6, 7, 0, 1, 2, 3},
        {5, 6, 7, 0, 1, 2, 3, 4},
        {6, 7, 0, 1, 2, 9, 4, 5}};

    EXPECT_THROW(grid.init(gridArray), std::out_of_range);
}