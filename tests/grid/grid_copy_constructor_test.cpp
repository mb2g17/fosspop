#include "grid/grid.hpp"

#include "gtest/gtest.h"

TEST(GridCopyConstructor, should_copy_grid_array)
{
    Grid src;
    Grid dst;

    src.init();
    dst = Grid(src);

    for (auto row = 0; row < 7; row++)
        for (auto col = 0; col < 8; col++)
            EXPECT_EQ(dst.getTile(row, col), src.getTile(row, col));
}

TEST(GridCopyConstructor, should_copy_whether_we_have_moves)
{
    Grid src;
    Grid dst;

    src.init();
    src.popAllCombinationsAndSpendMove();
    dst = Grid(src);

    EXPECT_EQ(dst.stillHaveMoves(), src.stillHaveMoves());
}

TEST(GridCopyConstructor, should_copy_whether_we_dont_have_moves)
{
    Grid src;
    Grid dst;

    src.init();
    while (src.stillHaveMoves())
    {
        src.popAllCombinationsAndSpendMove();
        src.moveAllTilesDown();
        src.fillInSpaces();
    }
    dst = Grid(src);

    EXPECT_EQ(dst.stillHaveMoves(), src.stillHaveMoves());
}