#include "ShipManager.h"

ShipManager::ShipManager(int shipsAmount, std::vector<int>& shipsSizes) : shipsAmount(shipsAmount)
{
    if (shipsAmount != shipsSizes.size())
    {
        throw std::invalid_argument("ships amount must be equal to length of ships sizes");
    }

    for (int size : shipsSizes)
    {
        ships.emplace_back(size);
    }
}

std::vector<int> ShipManager::getShipsSizes() const {
    std::vector<int> shipLengths;
    
    for (const Ship& ship : ships) {
        shipLengths.push_back(static_cast<int>(ship.getSize()));
    }

    return shipLengths;
}

Ship& ShipManager::getShip(int index)
{
    return ships[index];
}

int ShipManager::getShipAmount() const
{
    return shipsAmount;
}

int ShipManager::getShipsSunked() const 
{   
    int amount = 0;
    for (const Ship& ship : ships) {
        if (ship.isSunk()) {
            amount++;
        }
    }
    return amount;
}

bool ShipManager::allShipsSunk() const 
{
    for (const Ship& ship : ships) {
        if (!ship.isSunk()) {
            return false;
        }
    }
    return true;
}