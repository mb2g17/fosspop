#pragma once

#include <cmath>
#include <set>

struct Position;

struct PositionComp
{
    bool operator()(const Position &lhs, const Position &rhs) const;
};

class PositionSet : public std::set<Position, PositionComp>
{
public:
    bool contains(const Position &pos);
};

struct Position
{
    int row;
    int col;

    Position(int row, int col);
    PositionSet getNeighbours();

    bool operator<(const Position &pos) const;
    int getHash() const;
};