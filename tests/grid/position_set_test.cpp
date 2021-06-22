#include "grid/position.hpp"

#include "gtest/gtest.h"

TEST(PositionSet, should_store_positions)
{
    PositionSet posSet;
    Position pos1(1, 1), pos2(2, 2), pos3(3, 3);

    posSet.insert(pos1);
    posSet.insert(pos2);
    posSet.insert(pos3);

    EXPECT_TRUE(posSet.find(pos1) != posSet.end());
    EXPECT_TRUE(posSet.find(pos2) != posSet.end());
    EXPECT_TRUE(posSet.find(pos3) != posSet.end());
}

TEST(PositionSet, should_not_store_duplicates)
{
    PositionSet posSet;
    Position pos1(1, 1), pos2(1, 1);

    posSet.insert(pos1);
    posSet.insert(pos2);

    EXPECT_TRUE(posSet.size() == 1);
}

TEST(PositionSet, positions_identify_by_their_values_alone)
{
    PositionSet posSet;
    Position pos1(1, 1), pos2(1, 1);

    posSet.insert(pos1);

    EXPECT_TRUE(posSet.find(pos1) != posSet.end());
    EXPECT_TRUE(posSet.find(pos2) != posSet.end());
}

TEST(PositionSet, contains_method_should_return_true_for_elements_in_set)
{
    PositionSet posSet;
    Position pos1(1, 1), pos2(2, 2), pos3(3, 3);

    posSet.insert(pos1);
    posSet.insert(pos2);
    posSet.insert(pos3);

    EXPECT_TRUE(posSet.contains(pos1));
    EXPECT_TRUE(posSet.contains(pos2));
    EXPECT_TRUE(posSet.contains(pos3));
}

TEST(PositionSet, contains_method_should_return_false_for_elements_not_in_set)
{
    PositionSet posSet;
    Position pos1(1, 1), pos2(2, 2), pos3(3, 3);

    EXPECT_FALSE(posSet.contains(pos1));
    EXPECT_FALSE(posSet.contains(pos2));
    EXPECT_FALSE(posSet.contains(pos3));
}