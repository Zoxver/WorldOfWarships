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
    ShipManager* shipManager = nullptr;

    bool isWithinBounds(int x, int y) const
    {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    bool isCellOccupied(int x, int y) const
    {
        return isWithinBounds(x, y) && field[y][x] == CellStatus::SHIP;
    }

    void validatePlacement(int x, int y, int size, Ship::Orientation orientation) const
    {
        int mx = (orientation == Ship::Orientation::HORIZONTAL) ? x + size - 1 : x;
        int my = (orientation == Ship::Orientation::HORIZONTAL) ? y : y + size - 1;

        if (!isWithinBounds(x, y) || !isWithinBounds(mx, my))
        {
            throw std::out_of_range("Ship cannot be placed outside the field");
        }

        int startX = x - 1;
        int startY = y - 1;
        int endX = (orientation == Ship::Orientation::HORIZONTAL) ? (x + size) : x + 1;
        int endY = (orientation == Ship::Orientation::HORIZONTAL) ? (y + 1) : (y + size);

        for (int i = startX; i <= endX; ++i)
        {
            for (int j = startY; j <= endY; ++j)
            {
                if (isCellOccupied(i, j))
                {
                    throw std::invalid_argument("Ship cannot touch another ship");
                }
            }
        }
    }

public:
    GameField(int width, int height);

    void setShipManager(ShipManager* manager);
    void printField() const;
    void placeShip(int shipIndex, int x, int y, Ship::Orientation orientation);
    void attackCell(int x, int y);
    CellStatus getCellStatus(int x, int y) const;
};

#endif