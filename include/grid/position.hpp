#pragma once

#include <cmath>
#include <set>

struct Position;

struct PositionComp
{
    bool operator()(const Position &lhs, const Position &rhs) const;
};

struct Position
{
    int row;
    int col;

    Position(int row, int col);
    std::set<Position, PositionComp> getNeighbours();

    bool operator<(const Position &pos) const;
    int getHash() const;
};