#include "GameField.h"


GameField::GameField(int width, int height) : width(width), height(height)
{
    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument("Width and height must be positive");
    }
    field = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width));
}

GameField::GameField(const GameField &other) : width(other.width), height(other.height), field(other.field), shipManager(other.shipManager)
{
}

GameField::GameField(GameField &&other) noexcept : width(other.width), height(other.height), field(std::move(other.field)), shipManager(other.shipManager)
{
    other.shipManager = nullptr;
}

GameField &GameField::operator=(const GameField &other)
{
    if(this == &other) return *this;

    width = other.width;
    height = other.height;
    field = other.field;
    shipManager = other.shipManager;

    return *this;
}

GameField &GameField::operator=(GameField &&other) noexcept
{
    if (this == &other) return *this;
    
    width = other.width;
    height = other.height;
    field = std::move(other.field);
    shipManager = other.shipManager;

    return *this;
    
}

void GameField::setShipManager(ShipManager* manager)
{
    shipManager = manager;
}

void GameField::setAbilityManager(AbilityManager* manager)
{
    abilityManager = manager;
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
        throw std::out_of_range("Ship cannot be placed outside the field");
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
                throw std::invalid_argument("Ship cannot touch another ship");
            }
        }
    }
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

void GameField::placeShip(int shipIndex, int x, int y, Ship::Orientation orientation)
{
    if (!shipManager)
    {
        throw std::runtime_error("ShipManager is not set");
    }

    Ship& ship = shipManager->getShip(shipIndex);
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

void GameField::attackCell(int x, int y)
{
    if (!isWithinBounds(x, y))
    {
        throw std::out_of_range("Attack coordinates are out of bounds");
    } 
    if (field[y][x].attack())
    {
        std::cout << "Hit at (" << x << ", " << y << ")\n";
        if (field[y][x].getShip()->isSunk())
        {
            abilityManager->getRandomAbility();
        }
    } else
    {
        std::cout << "Miss at (" << x << ", " << y << ")\n";
    }
}

void GameField::randomFire() 
{
    int x, y;
    bool hit = false;

    while (!hit) 
    {
        x = rand() % width;
        y = rand() % height;
        if (field[y][x].getShip())
        {
            attackCell(x, y);
            hit = true;
        }
    }
}