#include <algorithm>
#include <random>
#include <chrono>

#include "grid/grid.hpp"

#include "gtest/gtest.h"

namespace GridCopyConstructorTest
{
    class GridCopyConstructorFixture : public testing::Test
    {
    public:
        Grid src, dst;

        GridCopyConstructorFixture()
        {
            src = Grid();
            src.init();
            randomlySetMovesAndScore(src);
            dst = Grid(src);
        }

        void randomlySetMovesAndScore(Grid &grid)
        {
            Random random = Random();
            auto newMoves = random.getRandomNumber(5, 10);
            auto newScore = random.getRandomNumber(10, 100);

            grid.getProps().addMoves(newMoves);
            grid.getProps().addScore(newScore);
        }
    };
}

using namespace GridCopyConstructorTest;

TEST_F(GridCopyConstructorFixture, should_copy_grid_array)
{
    for (auto row = 0; row < 7; row++)
        for (auto col = 0; col < 8; col++)
            EXPECT_EQ(dst.getTile(row, col), src.getTile(row, col));
}

TEST_F(GridCopyConstructorFixture, should_copy_moves)
{
    EXPECT_EQ(dst.getProps().getMoves(), src.getProps().getMoves());
}

TEST_F(GridCopyConstructorFixture, should_copy_score)
{
    EXPECT_EQ(dst.getProps().getScore(), src.getProps().getScore());
}