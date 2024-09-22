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

std::pair<int, int> ShipManager::getShipStartCoordinates(int x, int y)
{
    int shipIndex = getShipIndexByCoordinates(x, y);
    if (shipIndex == -1)
    {
        return {-1, -1};
    }

    std::pair<int, int> startCoordinates = {x, y};

    for (const auto& pair : shipCoordinatesMap)
    {
        if (pair.second == shipIndex)
        {
            startCoordinates.first = std::min(startCoordinates.first, pair.first.first);
            startCoordinates.second = std::min(startCoordinates.second, pair.first.second);
        }
    }
    return startCoordinates;
}

void ShipManager::attackShip(int shipIndex, int segmentIndex)
{
    validateShipIndex(shipIndex);
    ships[shipIndex].damageSegment(segmentIndex);
}

void ShipManager::addShipCoordinates(int index, int x, int y)
{
    shipCoordinatesMap[{x, y}] = index;
}

int ShipManager::getShipIndexByCoordinates(int x, int y) const
{
    auto it = shipCoordinatesMap.find({x, y});
    return (it != shipCoordinatesMap.end()) ? it->second : -1;
}

int ShipManager::getShipAmount() const
{
    return shipsAmount;
}