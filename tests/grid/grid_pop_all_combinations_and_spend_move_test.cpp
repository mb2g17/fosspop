#include "grid/grid.hpp"

#include "gtest/gtest.h"

#include "grid_assert.hpp"

TEST(GridPopAllCombinationsAndSpendMove, should_deduct_move)
{
    auto grid = Grid();
    grid.init();
    auto oldMoves = grid.getProps().getMoves();

    grid.popAllCombinationsAndSpendMove();
    auto newMoves = grid.getProps().getMoves();

    EXPECT_EQ(oldMoves, newMoves + 1);
}

TEST(GridPopAllCombinationsAndSpendMove, should_pop_combinations)
{
    int emptyGrid[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};

    int gridArray[7][8] = {
        {0, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, 0},
        {0, -1, -1, -1, -1, -1, -1, 0},
        {-1, -1, -1, -1, -1, -1, -1, 0},
        {0, 0, 0, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 0, 0, 0, -1, -1, -1, -1}};

    auto grid = Grid();
    grid.init(gridArray);
    grid.popAllCombinationsAndSpendMove();

    assertGrid(&grid, emptyGrid);
}