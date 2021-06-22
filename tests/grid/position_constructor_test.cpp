#include "grid/position.hpp"

#include "gtest/gtest.h"

#include <stdexcept>

TEST(PositionConstructor, should_set_row_and_col)
{
    Position pos(3, 4);
    EXPECT_EQ(pos.row, 3);
    EXPECT_EQ(pos.col, 4);
}

TEST(PositionConstructor, should_not_set_row_too_low)
{
    EXPECT_THROW(Position(-1, 4), std::out_of_range);
}

TEST(PositionConstructor, should_not_set_row_too_high)
{
    EXPECT_THROW(Position(7, 4), std::out_of_range);
}

TEST(PositionConstructor, should_not_set_col_too_low)
{
    EXPECT_THROW(Position(3, -1), std::out_of_range);
}

TEST(PositionConstructor, should_not_set_col_too_high)
{
    EXPECT_THROW(Position(3, 8), std::out_of_range);
}