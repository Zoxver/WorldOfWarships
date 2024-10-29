#ifndef CELL_H
#define CELL_H

#include <iostream>
#include "Ship.h"

class Cell {
public:
    enum class CellStatus
    {
        unknown,
        empty,
        ship
    };

private:
    CellStatus status;
    bool attacked;
    Ship* ship;
    int segmentIndex;

public:
    Cell();

    CellStatus getStatus() const;
    Ship* getShip() const;
    int getSegmentIndex() const;
    void setShip(Ship* shipPtr);
    void setSegmentIndex(int segmentIndex);
    bool attack(bool attack = true);
    void printCell(bool isForEnemy) const;
};

#endif