#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <stdexcept>
#include <iostream>
#include <vector>
#include "ShipManager.h"

class GameField
{
public:
    enum class CellStatus
    {
        UNKNOWN,
        EMPTY,
        SHIP
    };

private:
    int width;
    int height;
    std::vector<std::vector<CellStatus>> field;
    std::vector<std::vector<CellStatus>> enemyField;
    ShipManager* shipManager = nullptr;
    ShipManager* enemyShipManager = nullptr;

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
    void setEnemyShipManager(ShipManager* manager);
    void printField(bool isEnemy = false) const;
    void placeShip(int shipIndex, int x, int y, Ship::Orientation orientation);
    void attackCell(int x, int y);
    CellStatus getCellStatus(int x, int y) const;
};

#endif