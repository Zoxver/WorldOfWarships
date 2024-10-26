#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <stdexcept>
#include <vector>
#include "ShipManager.h"
#include "Cell.h"

class GameField
{

private:
    int width;
    int height;
    std::vector<std::vector<Cell>> field;
    ShipManager* shipManager = nullptr;

    bool isWithinBounds(int x, int y) const;
    bool isCellOccupied(int x, int y) const;
    void validatePlacement(int x, int y, int size, Ship::Orientation orientation) const;

public:
    GameField(int width, int height);
    GameField(const GameField &other);
    GameField(GameField &&other) noexcept;

    GameField &operator=(const GameField &other);
    GameField &operator=(GameField &&other) noexcept;

    void setShipManager(ShipManager* manager);
    void printField(bool isForEnemy = true) const;
    std::pair<int, int> getShipStartCoordinates(Ship& ship);
    void placeShip(int shipIndex, int x, int y, Ship::Orientation orientation);
    void attackCell(int x, int y);
};

#endif