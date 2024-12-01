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
    //ShipManager() {};
    ShipManager(int shipsAmount, std::vector<int>& shipsSizes);
    
    Ship& getShip(int index);
    int getShipAmount() const;
    int getShipsSunked() const;
    std::vector<int> getShipsSizes() const;
    bool allShipsSunk() const;
};

#endif