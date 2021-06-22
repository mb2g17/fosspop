#include "grid/position.hpp"

#include <stdexcept>

bool PositionSet::contains(const Position &pos)
{
    return this->find(pos) != this->end();
}

bool PositionComp::operator()(const Position &lhs, const Position &rhs) const
{
    return lhs < rhs;
}

Position::Position(int row, int col) : row(row), col(col)
{
    if (row < 0)
        throw std::out_of_range("Row cannot be negative");
    if (row > 6)
        throw std::out_of_range("Row cannot be over 6");
    if (col < 0)
        throw std::out_of_range("Col cannot be negative");
    if (col > 7)
        throw std::out_of_range("Col cannot be over 7");
}

PositionSet Position::getNeighbours()
{
    PositionSet neighbours;

    if (row > 0)
        neighbours.insert(Position(row - 1, col));
    if (row < 6)
        neighbours.insert(Position(row + 1, col));
    if (col > 0)
        neighbours.insert(Position(row, col - 1));
    if (col < 7)
        neighbours.insert(Position(row, col + 1));

    return neighbours;
}

bool Position::operator<(const Position &pos) const
{
    auto leftHash = this->getHash();
    auto rightHash = pos.getHash();
    return leftHash < rightHash;
}

int Position::getHash() const
{
    return pow(2, row) * pow(3, col);
}