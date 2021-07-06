#include "grid/grid.hpp"

#include "gtest/gtest.h"

namespace GridPopTileTest
{
    class GridPopTileFixture : public testing::Test
    {
    public:
        Grid grid;

        GridPopTileFixture()
        {
            int gridArray[7][8] = {
                {0, 1, 2, 3, 4, 5, 6, 3},
                {1, 2, 3, 4, 5, 6, 3, 0},
                {2, 3, 1, 5, 6, 3, 0, 1},
                {3, 4, 5, 6, 3, 0, 1, 2},
                {4, 5, 6, 3, 0, 1, 2, 3},
                {5, 6, 3, 0, 1, 2, 3, 4},
                {6, 3, 0, 1, 2, 2, 4, 5}};
            this->grid = Grid();
            this->grid.init(gridArray);
        }
    };
}

using namespace GridPopTileTest;

TEST_F(GridPopTileFixture, should_pop_tile_to_minus_one)
{
    for (auto row = 0; row < 7; row++)
    {
        for (auto col = 0; col < 8; col++)
        {
            grid.popTile(row, col);
            EXPECT_EQ(grid.getTile(row, col), -1);
        }
    }
}

TEST_F(GridPopTileFixture, should_not_pop_tile_out_of_range_left)
{
    EXPECT_THROW(grid.popTile(0, -1), std::out_of_range);
}

TEST_F(GridPopTileFixture, should_not_pop_tile_out_of_range_right)
{
    EXPECT_THROW(grid.popTile(0, 8), std::out_of_range);
}

TEST_F(GridPopTileFixture, should_not_pop_tile_out_of_range_top)
{
    EXPECT_THROW(grid.popTile(-1, 0), std::out_of_range);
}

TEST_F(GridPopTileFixture, should_not_pop_tile_out_of_range_bottom)
{
    EXPECT_THROW(grid.popTile(7, -1), std::out_of_range);
}