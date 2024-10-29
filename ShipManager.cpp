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

Ship& ShipManager::getShip(int index)
{
    return ships[index];
}

int ShipManager::getShipAmount() const
{
    return shipsAmount;
}