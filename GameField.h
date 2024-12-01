#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <stdexcept>
#include <vector>
#include "ShipManager.h"
#include "Cell.h"
#include "AbilityManager.h"

class GameField
{

private:
    int width;
    int height;
    std::vector<std::vector<Cell>> field;

    bool isWithinBounds(int x, int y) const;
    bool isCellOccupied(int x, int y) const;
    void validatePlacement(int x, int y, int size, Ship::Orientation orientation) const;

public:
    //GameField() {};
    GameField(int width, int height);
    GameField(const GameField &other);
    GameField(GameField &&other) noexcept;

    GameField &operator=(const GameField &other);
    GameField &operator=(GameField &&other) noexcept;

    std::vector<std::vector<Cell>> getField() const;
    int getWidth() const;
    int getHeight() const;
    void printField(bool isForEnemy = true, int startX = 0, int startY = 0, int endX = -1, int endY = -1) const;
    std::pair<int, int> getShipStartCoordinates(Ship& ship);
    void placeShip(Ship& ship, int x, int y, Ship::Orientation orientation);
    bool attackCell(int x, int y, int damage = 1, bool attack = true);
};

#endif