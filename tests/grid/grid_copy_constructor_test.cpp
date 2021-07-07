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
            auto seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::random_device rd;
            auto rng = std::mt19937(rd());

            auto movesDistribution = std::uniform_int_distribution<int>(5, 10);
            auto newMoves = movesDistribution(rng);

            auto scoreDistribution = std::uniform_int_distribution<int>(10, 100);
            auto newScore = scoreDistribution(rng);

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