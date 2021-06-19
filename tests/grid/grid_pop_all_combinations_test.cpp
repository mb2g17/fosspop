#include "grid/grid.hpp"

#include "gtest/gtest.h"

#include "grid_assert.hpp"

namespace GridPopAllCombinationsTest
{
    class GridPopAllCombinationsFixture : public testing::Test
    {
    public:
        Grid *grid;

        GridPopAllCombinationsFixture()
        {
            this->grid = new Grid();
        }

        ~GridPopAllCombinationsFixture()
        {
            delete this->grid;
        }
    };
}

using namespace GridPopAllCombinationsTest;

int emptyGrid[7][8] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1}};

/* ----------------
 * SHOULD POP
 * ---------------- */
TEST_F(GridPopAllCombinationsFixture, should_pop_3)
{
    // o o o
    int gridArray[7][8] = {
        {0, 0, 0, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};
    grid->init(gridArray);

    grid->popAllCombinations();

    assertGrid(grid, emptyGrid);
}

TEST_F(GridPopAllCombinationsFixture, should_pop_4)
{
    // o o o o
    int gridArray[7][8] = {
        {0, 0, 0, 0, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};
    grid->init(gridArray);

    grid->popAllCombinations();

    assertGrid(grid, emptyGrid);
}

TEST_F(GridPopAllCombinationsFixture, should_pop_5)
{
    // o o o o o
    int gridArray[7][8] = {
        {0, 0, 0, 0, 0, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1}};
    grid->init(gridArray);

    grid->popAllCombinations();

    assertGrid(grid, emptyGrid);
}

TEST_F(GridPopAllCombinationsFixture, should_pop_big_corners)
{
    // o o o
    // o
    // o
    int gridArray[7][8] = {
        {0, 0, 0, -1, 0, -1, -1, -1},
        {0, -1, -1, -1, 0, -1, -1, -1},
        {0, -1, -1, -1, 0, 0, 0, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 0, 0, -1, -1, -1, 0, -1},
        {-1, -1, 0, -1, -1, -1, 0, -1},
        {-1, -1, 0, -1, 0, 0, 0, -1}};
    grid->init(gridArray);

    grid->popAllCombinations();

    assertGrid(grid, emptyGrid);
}

/* Could also do:
 * o
 * o o o
 * o
 * o
 * ... but I'll leave that out for now */

/* ----------------------
 * SHOULD NOT (FULLY) POP
 * ---------------------- */
TEST_F(GridPopAllCombinationsFixture, should_not_pop_corners)
{
    // o
    // o o
    int gridArray[7][8] = {
        {0, 0, -1, 0, -1, -1, -1, -1},
        {0, -1, -1, 0, 0, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 0, -1, 0, 0, -1, -1, -1},
        {-1, 0, -1, -1, 0, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};
    grid->init(gridArray);

    grid->popAllCombinations();

    assertGrid(grid, gridArray); // Should not change
}

TEST_F(GridPopAllCombinationsFixture, should_not_pop_L_vertical)
{
    // o
    // o
    // o o
    int gridArray[7][8] = {
        {0, -1, -1, 0, 0, -1, -1, -1},
        {0, -1, -1, -1, 0, -1, -1, -1},
        {0, 0, -1, -1, 0, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, 0, -1, 0, 0, -1, -1, -1},
        {-1, 0, -1, 0, -1, -1, -1, -1},
        {0, 0, -1, 0, -1, -1, -1, -1}};
    grid->init(gridArray);

    grid->popAllCombinations();

    int expectedGridArray[7][8] = {
        {-1, -1, -1, 0, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, 0, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, 0, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1}};

    assertGrid(grid, expectedGridArray);
}

TEST_F(GridPopAllCombinationsFixture, should_not_pop_L_horizontal)
{
    // o o o
    // o
    int gridArray[7][8] = {
        {0, 0, 0, -1, 0, -1, -1, -1},
        {0, -1, -1, -1, 0, 0, 0, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 0, 0, -1, -1, -1, 0, -1},
        {-1, -1, 0, -1, 0, 0, 0, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};
    grid->init(gridArray);

    grid->popAllCombinations();

    int expectedGridArray[7][8] = {
        {-1, -1, -1, -1, 0, -1, -1, -1},
        {0, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, 0, -1},
        {-1, -1, 0, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};

    assertGrid(grid, expectedGridArray);
}

TEST_F(GridPopAllCombinationsFixture, should_not_pop_filled_big_corners)
{
    // o o o
    // o o
    // o
    int gridArray[7][8] = {
        {0, 0, 0, -1, 0, -1, -1, -1},
        {0, 0, -1, -1, 0, 0, -1, -1},
        {0, -1, -1, -1, 0, 0, 0, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {0, 0, 0, -1, -1, -1, 0, -1},
        {-1, 0, 0, -1, -1, 0, 0, -1},
        {-1, -1, 0, -1, 0, 0, 0, -1}};
    grid->init(gridArray);

    grid->popAllCombinations();

    int expectedGridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, 0, -1, -1, -1, 0, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, 0, -1, -1, -1, 0, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};

    assertGrid(grid, expectedGridArray);
}