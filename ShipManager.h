#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <vector>
#include <unordered_map>
#include <stdexcept>
#include "Ship.h"

class ShipManager
{
private:
    struct hashPair
    {
        template <class T1, class T2>
        size_t operator()(const std::pair<T1, T2>& p) const
        {
            size_t hash1 = std::hash<T1>{}(p.first);
            size_t hash2 = std::hash<T2>{}(p.second);
            return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
        }
    };

    int shipsAmount;
    std::vector<Ship> ships;
    std::unordered_map<std::pair<int, int>, int, hashPair> shipCoordinatesMap;

    void validateShipIndex(int index) const;

public:
    ShipManager(int shipsAmount, std::initializer_list<int> shipsSizes);

    Ship& getShip(int index);
    std::pair<int, int> getShipStartCoordinates(int x, int y);
    void attackShip(int shipIndex, int segmentIndex);
    void addShipCoordinates(int index, int x, int y);
    int getShipIndexByCoordinates(int x, int y) const;
    int getShipAmount() const;
};

#endif