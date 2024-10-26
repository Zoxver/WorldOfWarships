#include "ShipManager.h"

ShipManager::ShipManager(int shipsAmount, std::initializer_list<int> shipsSizes) : shipsAmount(shipsAmount)
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

void ShipManager::validateShipIndex(int index) const
{
    if (index < 0 || index >= shipsAmount)
    {
        throw std::out_of_range("Invalid ship index");
    }
}

Ship& ShipManager::getShip(int index)
{
    validateShipIndex(index);
    return ships[index];
}

int ShipManager::getShipAmount() const
{
    return shipsAmount;
}