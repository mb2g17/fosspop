#include "grid/grid.hpp"

#include "gtest/gtest.h"

namespace GridTest
{
    class GridFixture : public testing::Test
    {
    public:
        Grid *grid;

        GridFixture()
        {
            this->grid = new Grid();
        }

        ~GridFixture()
        {
            delete this->grid;
        }
    };
}

using namespace GridTest;

TEST_F(GridFixture, tiles_should_be_negative_preinit)
{
    for (int col = 0; col < 8; col++)
        for (int row = 0; row < 7; row++)
            EXPECT_EQ(grid->getTile(row, col), -1);
}

TEST_F(GridFixture, should_not_fetch_invalid_tile_positions)
{
    grid->init();
    EXPECT_THROW(grid->getTile(-1, -5), std::out_of_range);
    EXPECT_THROW(grid->getTile(8, 12), std::out_of_range);
}

TEST_F(GridFixture, tiles_should_be_nonnegative_postinit)
{
    grid->init();

    for (int col = 0; col < 8; col++)
        for (int row = 0; row < 7; row++)
            EXPECT_GT(grid->getTile(row, col), -1);
}

TEST_F(GridFixture, init_grid_should_be_fetched_with_gettile)
{
    int gridArray[7][8] = {
        {0, 1, 2, 3, 4, 5, 6, 7},
        {0, 1, 2, 3, 4, 5, 6, 7},
        {0, 1, 2, 3, 4, 5, 6, 7},
        {0, 1, 2, 3, 4, 5, 6, 7},
        {0, 1, 2, 3, 4, 5, 6, 7},
        {0, 1, 2, 3, 4, 5, 6, 7},
        {0, 1, 2, 3, 4, 5, 6, 7}};
    grid->init(gridArray);

    for (int col = 0; col < 8; col++)
        for (int row = 0; row < 7; row++)
            EXPECT_EQ(grid->getTile(row, col), gridArray[row][col]);
}

TEST_F(GridFixture, should_not_swap_preinit)
{
    EXPECT_THROW(grid->swap(0, 0, 1, 0), std::runtime_error);
}

TEST_F(GridFixture, should_not_swap_diagonally)
{
    grid->init();
    EXPECT_THROW(grid->swap(0, 0, 1, 1), std::invalid_argument);
}

TEST_F(GridFixture, should_not_swap_invalid_positions)
{
    grid->init();
    EXPECT_THROW(grid->swap(-1, 9, -1, -3), std::out_of_range);
}

TEST_F(GridFixture, should_swap_postinit)
{
    int gridArray[7][8] = {
        {0, 1, 2, 3, 4, 5, 6, 7},
        {1, 2, 3, 4, 5, 6, 7, 0},
        {2, 3, 4, 5, 6, 7, 0, 1},
        {3, 4, 5, 6, 7, 0, 1, 2},
        {4, 5, 6, 7, 0, 1, 2, 3},
        {5, 6, 7, 0, 1, 2, 3, 4},
        {6, 7, 0, 1, 2, 3, 4, 5}};
    grid->init(gridArray);

    grid->swap(0, 0, 0, 7);

    EXPECT_EQ(grid->getTile(0, 0), 7);
    EXPECT_EQ(grid->getTile(0, 7), 0);
}