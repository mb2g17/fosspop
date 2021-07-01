#include "grid/properties.hpp"

#include "gtest/gtest.h"

// --------------*
// -- No lock
// --------------*

TEST(Properties, should_add_moves)
{
    Properties prop = Properties();
    prop.addMoves(1);

    EXPECT_EQ(prop.getMoves(), 31);
}

TEST(Properties, should_add_score)
{
    Properties prop = Properties();
    prop.addScore(20);

    EXPECT_EQ(prop.getScore(), 20);
}

TEST(Properties, should_subtract_moves)
{
    Properties prop = Properties();
    prop.subtractMoves(1);

    EXPECT_EQ(prop.getMoves(), 29);
}

TEST(Properties, should_subtract_score)
{
    Properties prop = Properties();
    prop.addScore(100);
    prop.subtractScore(30);

    EXPECT_EQ(prop.getScore(), 70);
}

// --------------*
// -- Lock
// --------------*

TEST(Properties, should_not_add_moves_after_lock)
{
    Properties prop = Properties();
    prop.lockProperties();
    prop.addMoves(1);

    EXPECT_EQ(prop.getMoves(), 30);
}

TEST(Properties, should_not_add_score_after_lock)
{
    Properties prop = Properties();
    prop.lockProperties();
    prop.addScore(20);

    EXPECT_EQ(prop.getScore(), 0);
}

TEST(Properties, should_not_subtract_moves_after_lock)
{
    Properties prop = Properties();
    prop.lockProperties();
    prop.subtractMoves(1);

    EXPECT_EQ(prop.getMoves(), 30);
}

TEST(Properties, should_not_subtract_score_after_lock)
{
    Properties prop = Properties();
    prop.lockProperties();
    prop.subtractScore(30);

    EXPECT_EQ(prop.getScore(), 0);
}

// --------------*
// -- Unlock
// --------------*

TEST(Properties, should_add_moves_after_unlock)
{
    Properties prop = Properties();
    prop.lockProperties();
    prop.addMoves(1);
    prop.unlockProperties();
    prop.addMoves(1);

    EXPECT_EQ(prop.getMoves(), 31);
}

TEST(Properties, should_add_score_after_unlock)
{
    Properties prop = Properties();
    prop.lockProperties();
    prop.addScore(20);
    prop.unlockProperties();
    prop.addScore(20);

    EXPECT_EQ(prop.getScore(), 20);
}

TEST(Properties, should_subtract_moves_after_unlock)
{
    Properties prop = Properties();
    prop.lockProperties();
    prop.subtractMoves(1);
    prop.unlockProperties();
    prop.subtractMoves(1);

    EXPECT_EQ(prop.getMoves(), 29);
}

TEST(Properties, should_subtract_score_after_unlock)
{
    Properties prop = Properties();
    prop.addScore(100);
    prop.lockProperties();
    prop.subtractScore(30);
    prop.unlockProperties();
    prop.subtractScore(30);

    EXPECT_EQ(prop.getScore(), 70);
}

// --------------*
// -- Other
// --------------*

TEST(Properties, should_still_have_moves_if_moves_counter_is_positive)
{
    Properties prop = Properties();
    EXPECT_TRUE(prop.stillHaveMoves());
}

TEST(Properties, should_not_have_moves_if_no_moves_left)
{
    Properties prop = Properties();
    prop.subtractMoves(30);
    EXPECT_FALSE(prop.stillHaveMoves());
}

TEST(Properties, should_not_subtract_moves_to_negative)
{
    Properties prop = Properties();
    prop.subtractMoves(60);
    EXPECT_EQ(prop.getMoves(), 0);
}

TEST(Properties, should_not_subtract_score_to_negative)
{
    Properties prop = Properties();
    prop.subtractScore(60);
    EXPECT_EQ(prop.getScore(), 0);
}