#include <random>

class Random
{
    unsigned int seed;
    std::mt19937 rng;
    std::uniform_int_distribution<int> tileDistribution;

public:
    Random();

    int getSeed();
    int getRandomTile();
    int getRandomNumber(int min, int max);
};