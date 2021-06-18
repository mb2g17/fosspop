#include "grid/grid.hpp"

#include "gtest/gtest.h"

namespace GridSwapTest
{
    class GridSwapFixture : public testing::Test
    {
    public:
        Grid *grid;

        GridSwapFixture()
        {
            this->grid = new Grid();
        }

        ~GridSwapFixture()
        {
            delete this->grid;
        }
    };
}

using namespace GridSwapTest;

TEST_F(GridSwapFixture, should_not_swap_preinit)
{
    EXPECT_THROW(grid->swap(0, 0, 1, 0), std::runtime_error);
}

TEST_F(GridSwapFixture, should_not_swap_diagonally)
{
    grid->init();
    EXPECT_THROW(grid->swap(0, 0, 1, 1), std::invalid_argument);
}

TEST_F(GridSwapFixture, should_not_swap_invalid_positions)
{
    grid->init();
    EXPECT_THROW(grid->swap(-1, 9, -1, -3), std::out_of_range);
}

TEST_F(GridSwapFixture, should_swap_col_left_to_right_postinit)
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

    EXPECT_EQ(grid->getTile(0, 0), 1);
    EXPECT_EQ(grid->getTile(0, 1), 2);
    EXPECT_EQ(grid->getTile(0, 2), 3);
    EXPECT_EQ(grid->getTile(0, 3), 4);
    EXPECT_EQ(grid->getTile(0, 4), 5);
    EXPECT_EQ(grid->getTile(0, 5), 6);
    EXPECT_EQ(grid->getTile(0, 6), 7);
    EXPECT_EQ(grid->getTile(0, 7), 0);
}

TEST_F(GridSwapFixture, should_swap_col_right_to_left_postinit)
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

    grid->swap(0, 7, 0, 0);

    EXPECT_EQ(grid->getTile(0, 0), 7);
    EXPECT_EQ(grid->getTile(0, 1), 0);
    EXPECT_EQ(grid->getTile(0, 2), 1);
    EXPECT_EQ(grid->getTile(0, 3), 2);
    EXPECT_EQ(grid->getTile(0, 4), 3);
    EXPECT_EQ(grid->getTile(0, 5), 4);
    EXPECT_EQ(grid->getTile(0, 6), 5);
    EXPECT_EQ(grid->getTile(0, 7), 6);
}

TEST_F(GridSwapFixture, should_swap_row_top_to_bottom_postinit)
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

    grid->swap(0, 0, 6, 0);

    EXPECT_EQ(grid->getTile(0, 0), 1);
    EXPECT_EQ(grid->getTile(1, 0), 2);
    EXPECT_EQ(grid->getTile(2, 0), 3);
    EXPECT_EQ(grid->getTile(3, 0), 4);
    EXPECT_EQ(grid->getTile(4, 0), 5);
    EXPECT_EQ(grid->getTile(5, 0), 6);
    EXPECT_EQ(grid->getTile(6, 0), 0);
}

TEST_F(GridSwapFixture, should_swap_row_bottom_to_top_postinit)
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

    grid->swap(6, 0, 0, 0);

    EXPECT_EQ(grid->getTile(0, 0), 6);
    EXPECT_EQ(grid->getTile(1, 0), 0);
    EXPECT_EQ(grid->getTile(2, 0), 1);
    EXPECT_EQ(grid->getTile(3, 0), 2);
    EXPECT_EQ(grid->getTile(4, 0), 3);
    EXPECT_EQ(grid->getTile(5, 0), 4);
    EXPECT_EQ(grid->getTile(6, 0), 5);
}