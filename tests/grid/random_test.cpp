#include "grid/random.hpp"

#include "gtest/gtest.h"

TEST(Random, should_get_tile)
{
    Random random = Random();
    int randomTile = random.getRandomTile();
    EXPECT_GE(randomTile, 0);
    EXPECT_LE(randomTile, 6);
}

TEST(Random, should_get_random_number_in_range)
{
    Random random = Random();
    int randomTile = random.getRandomNumber(10, 20);
    EXPECT_GE(randomTile, 10);
    EXPECT_LE(randomTile, 20);
}

TEST(Random, seed_should_increment)
{
    Random random = Random();
    int initialSeed = random.getSeed();
    int afterSeed = random.getSeed();

    EXPECT_EQ(initialSeed + 1, afterSeed);
}