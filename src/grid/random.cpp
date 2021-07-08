#include <algorithm>
#include <random>
#include <chrono>

#include "grid/random.hpp"

Random::Random()
{
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::random_device rd;
    rng = std::mt19937(rd());
    tileDistribution = std::uniform_int_distribution<int>(0, 6);
}

int Random::getRandomTile()
{
    return tileDistribution(rng);
}

int Random::getRandomNumber(int min, int max)
{
    auto distribution = std::uniform_int_distribution<int>(min, max);
    return distribution(rng);
}

int Random::getSeed()
{
    return seed++;
}