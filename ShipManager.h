#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <vector>
#include <stdexcept>
#include "Ship.h"

class ShipManager
{
private:

    int shipsAmount;
    std::vector<Ship> ships;

public:
    ShipManager(int shipsAmount, std::initializer_list<int> shipsSizes);
    
    Ship& getShip(int index);
    int getShipAmount() const;
};

#endif