#include <algorithm>

#include "grid/properties.hpp"

int Properties::getMoves()
{
    return moves;
}

int Properties::getScore()
{
    return score;
}

void Properties::addMoves(int delta)
{
    if (!isLocked)
        moves += delta;
}

void Properties::subtractMoves(int delta)
{
    if (!isLocked)
        moves = std::max(moves - delta, 0);
}

void Properties::addScore(int delta)
{
    if (!isLocked)
        score += delta;
}
void Properties::subtractScore(int delta)
{
    if (!isLocked)
        score = std::max(score - delta, 0);
}

void Properties::lockProperties()
{
    isLocked = true;
}

void Properties::unlockProperties()
{
    isLocked = false;
}

bool Properties::stillHaveMoves()
{
    return moves > 0;
}