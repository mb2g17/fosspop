#include "grid/grid.hpp"

#include "gtest/gtest.h"

TEST(GridIsCombinationAnywhere, should_return_true_when_three_is_present)
{
    // o o o
    int gridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, 0, 0, 0, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};
    auto grid = Grid();
    grid.init(gridArray);

    EXPECT_TRUE(grid.isCombinationAnywhere());
}

TEST(GridIsCombinationAnywhere, should_return_true_when_four_is_present)
{
    // o o o o
    int gridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, 0, 0, 0, 0, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};
    auto grid = Grid();
    grid.init(gridArray);

    EXPECT_TRUE(grid.isCombinationAnywhere());
}

TEST(GridIsCombinationAnywhere, should_return_true_when_five_is_present)
{
    // o o o o o
    int gridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, 0, 0, 0, 0, 0},
        {-1, -1, -1, -1, -1, -1, -1, -1}};
    auto grid = Grid();
    grid.init(gridArray);

    EXPECT_TRUE(grid.isCombinationAnywhere());
}

TEST(GridIsCombinationAnywhere, should_return_true_when_multiple_combs_in_vein)
{
    // o o o
    // o
    // o o o o
    // o
    // o
    int gridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, 0, 0, 0, -1, -1, -1, -1},
        {-1, 0, -1, -1, -1, -1, -1, -1},
        {-1, 0, 0, 0, 0, -1, -1, -1},
        {-1, 0, -1, -1, -1, -1, -1, -1},
        {-1, 0, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};
    auto grid = Grid();
    grid.init(gridArray);

    EXPECT_TRUE(grid.isCombinationAnywhere());
}

TEST(GridIsCombinationAnywhere, should_return_false_when_nothing_is_present)
{
    int gridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}};
    auto grid = Grid();
    grid.init(gridArray);

    EXPECT_FALSE(grid.isCombinationAnywhere());
}

TEST(GridIsCombinationAnywhere, should_return_false_when_corner_is_present)
{
    // o o
    // o
    int gridArray[7][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, 0, 0, -1, 0, 0, -1},
        {-1, -1, 0, -1, -1, -1, 0, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, 0, -1, -1, -1, 0, -1},
        {-1, -1, 0, 0, -1, 0, 0, -1}};
    auto grid = Grid();
    grid.init(gridArray);

    EXPECT_FALSE(grid.isCombinationAnywhere());
}