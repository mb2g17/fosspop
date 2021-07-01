#include "grid/properties.hpp"

int Properties::getMoves()
{
    return this->moves;
}
int Properties::getScore()
{
    return this->score;
}

void Properties::addMoves(int delta)
{
    if (!this->isLocked)
        this->moves += delta;
}

void Properties::subtractMoves(int delta)
{
    if (!this->isLocked)
        this->moves -= delta;
}

void Properties::addScore(int delta)
{
    if (!this->isLocked)
        this->score += delta;
}
void Properties::subtractScore(int delta)
{
    if (!this->isLocked)
        this->score -= delta;
}

void Properties::lockProperties()
{
    this->isLocked = true;
}
void Properties::unlockProperties()
{
    this->isLocked = false;
}
