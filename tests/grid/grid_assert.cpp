#include "grid/grid.hpp"

#include "gtest/gtest.h"

#include "grid_assert.hpp"

void assertGrid(Grid *grid, int expectedGridArray[7][8])
{
    for (auto row = 0; row < 7; row++)
        for (auto col = 0; col < 8; col++)
            EXPECT_EQ(grid->getTile(row, col), expectedGridArray[row][col]);
}