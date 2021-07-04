#include "grid/grid.hpp"

#include "gtest/gtest.h"

#include "grid_assert.hpp"

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
        {0, 1, 2, 3, 4, 5, 6, 3}, // <-- 0 on far left
        {1, 2, 3, 4, 5, 6, 3, 0},
        {2, 3, 4, 5, 6, 3, 0, 1},
        {3, 4, 5, 6, 3, 0, 1, 2},
        {4, 5, 6, 3, 0, 1, 2, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};
    grid->init(gridArray);

    grid->swap(0, 0, 0, 7);

    int expectedGridArray[7][8] = {
        {1, 2, 3, 4, 5, 6, 3, 0}, // <-- 0 on far right
        {1, 2, 3, 4, 5, 6, 3, 0},
        {2, 3, 4, 5, 6, 3, 0, 1},
        {3, 4, 5, 6, 3, 0, 1, 2},
        {4, 5, 6, 3, 0, 1, 2, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    assertGrid(grid, expectedGridArray);
}

TEST_F(GridSwapFixture, should_swap_col_right_to_left_postinit)
{
    int gridArray[7][8] = {
        {0, 1, 2, 3, 4, 5, 6, 3}, // <-- 3 on far right
        {1, 2, 3, 4, 5, 6, 3, 0},
        {2, 3, 4, 5, 6, 3, 0, 1},
        {3, 4, 5, 6, 3, 0, 1, 2},
        {4, 5, 6, 3, 0, 1, 2, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};
    grid->init(gridArray);

    grid->swap(0, 7, 0, 0);

    int expectedGridArray[7][8] = {
        {3, 0, 1, 2, 3, 4, 5, 6}, // <-- 3 on far left
        {1, 2, 3, 4, 5, 6, 3, 0},
        {2, 3, 4, 5, 6, 3, 0, 1},
        {3, 4, 5, 6, 3, 0, 1, 2},
        {4, 5, 6, 3, 0, 1, 2, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};

    assertGrid(grid, expectedGridArray);
}

TEST_F(GridSwapFixture, should_swap_row_top_to_bottom_postinit)
{
    int gridArray[7][8] = {
        {0, 1, 2, 3, 4, 5, 6, 3}, // <-- 0 at the top
        {1, 2, 3, 4, 5, 6, 3, 0},
        {2, 3, 4, 5, 6, 3, 0, 1},
        {3, 4, 5, 6, 3, 0, 1, 2},
        {4, 5, 6, 3, 0, 1, 2, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}};
    grid->init(gridArray);

    grid->swap(0, 0, 6, 0);

    int expectedGridArray[7][8] = {
        {1, 1, 2, 3, 4, 5, 6, 3},
        {2, 2, 3, 4, 5, 6, 3, 0},
        {3, 3, 4, 5, 6, 3, 0, 1},
        {4, 4, 5, 6, 3, 0, 1, 2},
        {5, 5, 6, 3, 0, 1, 2, 3},
        {6, 6, 3, 0, 1, 2, 3, 4},
        {0, 3, 0, 1, 2, 3, 4, 5}}; // <-- 0 at the bottom

    assertGrid(grid, expectedGridArray);
}

TEST_F(GridSwapFixture, should_swap_row_bottom_to_top_postinit)
{
    int gridArray[7][8] = {
        {0, 1, 2, 3, 4, 5, 6, 3},
        {1, 2, 3, 4, 5, 6, 3, 0},
        {2, 3, 4, 5, 6, 3, 0, 1},
        {3, 4, 5, 6, 3, 0, 1, 2},
        {4, 5, 6, 3, 0, 1, 2, 3},
        {5, 6, 3, 0, 1, 2, 3, 4},
        {6, 3, 0, 1, 2, 3, 4, 5}}; // <-- 6 at the bottom
    grid->init(gridArray);

    grid->swap(6, 0, 0, 0);

    int expectedGridArray[7][8] = {
        {6, 1, 2, 3, 4, 5, 6, 3}, // <-- 6 at the top
        {0, 2, 3, 4, 5, 6, 3, 0},
        {1, 3, 4, 5, 6, 3, 0, 1},
        {2, 4, 5, 6, 3, 0, 1, 2},
        {3, 5, 6, 3, 0, 1, 2, 3},
        {4, 6, 3, 0, 1, 2, 3, 4},
        {5, 3, 0, 1, 2, 3, 4, 5}};

    assertGrid(grid, expectedGridArray);
}