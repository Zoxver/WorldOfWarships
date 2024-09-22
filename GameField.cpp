#include "GameField.h"

GameField::GameField(int width, int height) : width(width), height(height)
{
    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument("Width and height must be positive");
    }
    field = std::vector<std::vector<CellStatus>>(height, std::vector<CellStatus>(width, CellStatus::UNKNOWN));
}

void GameField::setShipManager(ShipManager* manager)
{
    shipManager = manager;
}

void GameField::printField() const
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            switch (field[y][x])
            {
            case CellStatus::UNKNOWN:
                std::cout << "? ";
                break;
            case CellStatus::EMPTY:
                std::cout << ". ";
                break;
            case CellStatus::SHIP:
                std::cout << "S ";
                break;
            }
        }
        std::cout << '\n';
    }
}

void GameField::placeShip(int shipIndex, int x, int y, Ship::Orientation orientation)
{
    if (!shipManager)
    {
        throw std::runtime_error("ShipManager is not set");
    }

    Ship& ship = shipManager->getShip(shipIndex);
    int size = static_cast<int>(ship.getSize());

    validatePlacement(x, y, size, orientation);

    int dx = (orientation == Ship::Orientation::HORIZONTAL) ? 1 : 0;
    int dy = (orientation == Ship::Orientation::HORIZONTAL) ? 0 : 1;

    for (int i = 0; i < size; ++i)
    {
        int xCord = x + i * dx;
        int yCord = y + i * dy;
        field[yCord][xCord] = CellStatus::SHIP;
        shipManager->addShipCoordinates(shipIndex, xCord, yCord);
    }
}

void GameField::attackCell(int x, int y)
{
    if (!isWithinBounds(x, y))
    {
        throw std::out_of_range("Attack coordinates are out of bounds");
    }

    if (field[y][x] == CellStatus::SHIP)
    {
        int shipIndex = shipManager->getShipIndexByCoordinates(x, y);
        std::pair<int, int> startCords = shipManager->getShipStartCoordinates(x, y);
        int segmentIndex = (x - startCords.first) + (y - startCords.second); // Упрощенное вычисление индекса
        shipManager->attackShip(shipIndex, segmentIndex);
        std::cout << "Hit at (" << x << ", " << y << ")\n";
    }
    else
    {
        std::cout << "Miss at (" << x << ", " << y << ")\n";
    }
}

GameField::CellStatus GameField::getCellStatus(int x, int y) const
{
    if (!isWithinBounds(x, y))
    {
        throw std::out_of_range("Coordinates are out of bounds");
    }
    return field[y][x];
}