#include "grid/grid.hpp"

#include "gtest/gtest.h"

namespace GridGetTileTest
{
    class GridGetTileFixture : public testing::Test
    {
    public:
        Grid *grid;

        GridGetTileFixture()
        {
            this->grid = new Grid();
        }

        ~GridGetTileFixture()
        {
            delete this->grid;
        }
    };
}

using namespace GridGetTileTest;

TEST_F(GridGetTileFixture, should_return_tile_number)
{
    int gridArray[7][8] = {
        {0, 1, -1, 3, 4, -1, 6, 3},
        {1, 2, -1, 4, 5, -1, 3, 0},
        {2, 3, 4, 5, 6, -1, 0, 1},
        {3, 4, 5, 6, 3, 0, 1, 2},
        {4, 5, 6, 3, 0, 1, 2, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};
    grid->init(gridArray);

    for (auto row = 0; row < 7; row++)
    {
        for (auto col = 0; col < 8; col++)
        {
            EXPECT_EQ(grid->getTile(row, col), gridArray[row][col]);
        }
    }
}

TEST_F(GridGetTileFixture, should_not_fetch_invalid_tile_positions)
{
    grid->init();
    EXPECT_THROW(grid->getTile(-1, -5), std::out_of_range);
    EXPECT_THROW(grid->getTile(8, 12), std::out_of_range);
}