#include "grid/grid.hpp"

#include "gtest/gtest.h"

namespace GridInitTest
{
    class GridInitFixture : public testing::Test
    {
    public:
        Grid *grid;

        GridInitFixture()
        {
            this->grid = new Grid();
        }

        ~GridInitFixture()
        {
            delete this->grid;
        }
    };
}

using namespace GridInitTest;

TEST_F(GridInitFixture, tiles_should_be_negative_preinit)
{
    for (int col = 0; col < 8; col++)
        for (int row = 0; row < 7; row++)
            EXPECT_EQ(grid->getTile(row, col), -1);
}

TEST_F(GridInitFixture, tiles_should_be_nonnegative_postinit)
{
    grid->init();

    for (int col = 0; col < 8; col++)
        for (int row = 0; row < 7; row++)
            EXPECT_GT(grid->getTile(row, col), -1);
}