#include "Cell.h"

Cell::Cell() : status(CellStatus::empty), attacked(false), ship(nullptr), segmentIndex(-1) {}

Cell::CellStatus Cell::getStatus() const { return status; }
Ship* Cell::getShip() const { return ship; }
int Cell::getSegmentIndex() const { return segmentIndex; }

void Cell::setShip(Ship* shipPtr) 
{
    status = CellStatus::ship;
    ship = shipPtr;
}

void Cell::setSegmentIndex(int index) 
{
    segmentIndex = index;
}

bool Cell::attack(bool attack, int damage) {
    if(!attacked)
    {
        attacked = attack;
    }
    if (ship) {
        ship->damageSegment(segmentIndex, damage);
        if (CellStatus::empty == status)
        {
            status = CellStatus::ship;
        }
        return true;
    } else {
        return false;
    }
}

void Cell::printCell(bool isForEnemy) const {
    if (!attacked && isForEnemy) {
        std::cout << "? ";
    } else {
        switch (status) {
        
        case CellStatus::empty:
            std::cout << ". ";
            break;
        case CellStatus::ship:

                switch (ship->getSegmentStatus(segmentIndex))
                {
                case Ship::SegmentHealth::intact:
                    std::cout << "S ";
                    break;
                case Ship::SegmentHealth::damaged:
                    std::cout << "+ ";
                    break;
                case Ship::SegmentHealth::destroyed:
                    std::cout << "X ";
                    break;
                }
                break;
        
        }
    }
}
