#include "grid/position.hpp"

#include "gtest/gtest.h"

#include <set>

#define ASSERT_NEIGHBOURS(INITIAL_ROW, INITIAL_COL, ...)                      \
    Position initialPos(INITIAL_ROW, INITIAL_COL);                            \
    std::set<Position, PositionComp> neighbours = initialPos.getNeighbours(); \
                                                                              \
    Position expectedPositions[] = {__VA_ARGS__};                             \
                                                                              \
    for (auto &position : expectedPositions)                                  \
        EXPECT_TRUE(neighbours.find(position) != neighbours.end());

/* ----------------
 * CENTRE
 * ---------------- */
TEST(PositionGetNeighbours, should_get_neighbours)
{
    ASSERT_NEIGHBOURS(3, 4,
                      Position(3, 5),
                      Position(3, 3),
                      Position(2, 4),
                      Position(4, 4));
}

/* ----------------
 * CORNERS
 * ---------------- */
TEST(PositionGetNeighbours, should_get_neighbours_top_left)
{
    ASSERT_NEIGHBOURS(0, 0,
                      Position(0, 1),
                      Position(1, 0));
}

TEST(PositionGetNeighbours, should_get_neighbours_top_right)
{
    ASSERT_NEIGHBOURS(0, 7,
                      Position(0, 6),
                      Position(1, 7));
}

TEST(PositionGetNeighbours, should_get_neighbours_bottom_left)
{
    ASSERT_NEIGHBOURS(6, 0,
                      Position(6, 1),
                      Position(5, 0));
}

TEST(PositionGetNeighbours, should_get_neighbours_bottom_right)
{
    ASSERT_NEIGHBOURS(6, 7,
                      Position(6, 6),
                      Position(5, 7));
}

/* ----------------
 * SIDES
 * ---------------- */
TEST(PositionGetNeighbours, should_get_neighbours_top)
{
    ASSERT_NEIGHBOURS(0, 4,
                      Position(1, 4),
                      Position(0, 3),
                      Position(0, 5));
}

TEST(PositionGetNeighbours, should_get_neighbours_bottom)
{
    ASSERT_NEIGHBOURS(6, 4,
                      Position(5, 4),
                      Position(6, 3),
                      Position(6, 5));
}

TEST(PositionGetNeighbours, should_get_neighbours_left)
{
    ASSERT_NEIGHBOURS(3, 0,
                      Position(3, 1),
                      Position(2, 0),
                      Position(4, 0));
}

TEST(PositionGetNeighbours, should_get_neighbours_right)
{
    ASSERT_NEIGHBOURS(3, 7,
                      Position(3, 6),
                      Position(2, 7),
                      Position(4, 7));
}
