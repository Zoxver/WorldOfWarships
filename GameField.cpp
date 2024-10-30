#include "GameField.h"
#include "AttackOutOfBoundsException.h"
#include "FieldSizeException.h"
#include "ShipPlacementException.h"

GameField::GameField(int width, int height) : width(width), height(height)
{
    if (width <= 0 || height <= 0)
    {
        throw FieldSizeException();
    }
    field = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
}

GameField::GameField(const GameField &other) : width(other.width), height(other.height), field(other.field)
{
}

GameField::GameField(GameField &&other) noexcept : width(other.width), height(other.height), field(std::move(other.field))
{
}

GameField &GameField::operator=(const GameField &other)
{
    if(this == &other) return *this;

    width = other.width;
    height = other.height;
    field = other.field;

    return *this;
}

GameField &GameField::operator=(GameField &&other) noexcept
{
    if (this == &other) return *this;
    
    width = other.width;
    height = other.height;
    field = std::move(other.field);
    return *this;
    
}

bool GameField::isWithinBounds(int x, int y) const
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool GameField::isCellOccupied(int x, int y) const
{
    return isWithinBounds(x, y) && field[y][x].getStatus() == Cell::CellStatus::ship;
}

void GameField::validatePlacement(int x, int y, int size, Ship::Orientation orientation) const
{
    int mx = (orientation == Ship::Orientation::horizontal) ? x + size - 1 : x;
    int my = (orientation == Ship::Orientation::horizontal) ? y : y + size - 1;

    if (!isWithinBounds(x, y) || !isWithinBounds(mx, my))
    {
        throw ShipPlacementException();
    }

    int startX = x - 1;
    int startY = y - 1;
    int endX = (orientation == Ship::Orientation::horizontal) ? (x + size) : x + 1;
    int endY = (orientation == Ship::Orientation::horizontal) ? (y + 1) : (y + size);

    for (int i = startX; i <= endX; ++i)
    {
        for (int j = startY; j <= endY; ++j)
        {
            if (isCellOccupied(i, j))
            {
                throw ShipPlacementException();
            }
        }
    }
}

bool GameField::getAbilityRequired() const
{
    return abilityRequired;
}

void GameField::printField(bool isForEnemy, int startX, int startY, int endX, int endY) const
{
    if (endX == -1) 
    {
        endX = width;
    }
    if (endY == -1) 
    {
        endY = height;
    }
    for (int y = startY; y < endY; ++y)
    {
        for (int x = startX; x < endX; ++x)
        {   
            if (isWithinBounds(x, y))
            {
                field[y][x].printCell(isForEnemy);
            }
            
        }
        std::cout << '\n';
    }
}

std::pair<int, int> GameField::getShipStartCoordinates(Ship& ship)
{
    std::pair<int, int> startCoordinates = {-1, -1};

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (field[y][x].getShip() == &ship)
            {
                startCoordinates = {x, y};
                return startCoordinates;
            }
        }
    }
    return startCoordinates;
}

void GameField::placeShip(Ship& ship, int x, int y, Ship::Orientation orientation)
{
    
    int size = static_cast<int>(ship.getSize());

    validatePlacement(x, y, size, orientation);

    int dx = (orientation == Ship::Orientation::horizontal) ? 1 : 0;
    int dy = (orientation == Ship::Orientation::horizontal) ? 0 : 1;

    for (int i = 0; i < size; ++i)
    {
        int xCord = x + i * dx;
        int yCord = y + i * dy;
        field[yCord][xCord].setShip(&ship);
        std::pair<int, int> startCords = getShipStartCoordinates(ship);
        int segmentIndex = (xCord - startCords.first) + (yCord - startCords.second);
        field[yCord][xCord].setSegmentIndex(segmentIndex);
    }
}

void GameField::attackCell(int x, int y, bool attack)
{
    if (!isWithinBounds(x, y))
    {
        throw AttackOutOfBoundsException();
    } 
    if (field[y][x].attack(attack))
    {   
        if (attack)
        {
            std::cout << "Попадание по координатам (" << x << ", " << y << ")\n";
        }
        if (field[y][x].getShip()->isSunk())
        {
            abilityRequired = true;
        }
    } else
    {
        std::cout << "Промах по координатам (" << x << ", " << y << ")\n";
    }
}

void GameField::randomFire() 
{
    std::vector<std::pair<int, int>> shipCells;

    for (int y = 0; y < height; ++y) 
    {
        for (int x = 0; x < width; ++x) 
        {
            if (field[y][x].getShip()) 
            {
                shipCells.emplace_back(x, y);
            }
        }
    }

    int randomIndex = rand() % shipCells.size();
    int x = shipCells[randomIndex].first;
    int y = shipCells[randomIndex].second;
    attackCell(x, y, false);

}