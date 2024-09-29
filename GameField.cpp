#include "GameField.h"

GameField::GameField(int width, int height) : width(width), height(height)
{
    if (width <= 0 || height <= 0)
    {
        throw std::invalid_argument("Width and height must be positive");
    }
    field = std::vector<std::vector<CellStatus>>(height, std::vector<CellStatus>(width, CellStatus::empty));
    enemyField = std::vector<std::vector<CellStatus>>(height, std::vector<CellStatus>(width, CellStatus::unknown));
}

GameField::GameField(const GameField &other) : width(other.width), height(other.height), field(other.field), shipManager(other.shipManager), enemyField(other.enemyField), enemyShipManager(other.enemyShipManager)
{
}

GameField::GameField(GameField &&other) noexcept : width(other.width), height(other.height), field(std::move(other.field)), shipManager(other.shipManager), enemyField(other.enemyField), enemyShipManager(other.enemyShipManager)
{
    other.shipManager = nullptr;
    other.enemyShipManager = nullptr;
}

GameField &GameField::operator=(const GameField &other)
{
    if(this == &other) return *this;

    width = other.width;
    height = other.height;
    field = other.field;
    shipManager = other.shipManager;
    enemyField = other.field;
    enemyShipManager = other.enemyShipManager;

    return *this;
}

GameField &GameField::operator=(GameField &&other) noexcept
{
    if (this == &other) return *this;
    
    width = other.width;
    height = other.height;
    field = std::move(other.field);
    shipManager = other.shipManager;
    enemyField = std::move(other.field);
    enemyShipManager = other.enemyShipManager;
    other.shipManager = nullptr;
    other.enemyShipManager = nullptr;

    return *this;
    
}

void GameField::setShipManager(ShipManager* manager)
{
    shipManager = manager;
}

void GameField::setEnemyShipManager(ShipManager* manager)
{
    enemyShipManager = manager;
}

bool GameField::isWithinBounds(int x, int y) const
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool GameField::isCellOccupied(int x, int y) const
{
    return isWithinBounds(x, y) && field[y][x] == CellStatus::ship;
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

void GameField::printField(bool isEnemy) const
{
    ShipManager* manager = isEnemy ? enemyShipManager : shipManager;
    const std::vector<std::vector<CellStatus>>& fieldToPrint = isEnemy ? enemyField : field;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            switch (fieldToPrint[y][x])
            {
            case CellStatus::unknown:
                std::cout << "? ";
                break;
            case CellStatus::empty:
                std::cout << ". ";
                break;
            case CellStatus::ship:
                int shipIndex = manager->getShipIndexByCoordinates(x, y);
                std::pair<int, int> startCords = manager->getShipStartCoordinates(x, y);
                int segmentIndex = (x - startCords.first) + (y - startCords.second);
                switch (manager->getShipSegmentStatus(shipIndex, segmentIndex))
                {
                case Ship::SegmentHealth::intact:
                    std::cout << "S ";
                    break;
                case Ship::SegmentHealth::damaged:
                    std::cout << "+ ";
                    break;
                case Ship::SegmentHealth::destroyed:
                    std::cout << "X ";
                    break;
                }
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

    int dx = (orientation == Ship::Orientation::horizontal) ? 1 : 0;
    int dy = (orientation == Ship::Orientation::horizontal) ? 0 : 1;

    for (int i = 0; i < size; ++i)
    {
        int xCord = x + i * dx;
        int yCord = y + i * dy;
        field[yCord][xCord] = CellStatus::ship;
        shipManager->addShipCoordinates(shipIndex, xCord, yCord);
    }
}

void GameField::attackCell(int x, int y)
{
    if (!isWithinBounds(x, y))
    {
        throw std::out_of_range("Attack coordinates are out of bounds");
    }
    
    int shipIndex = enemyShipManager->getShipIndexByCoordinates(x, y);
    if (shipIndex != -1)
    {
        std::pair<int, int> startCords = enemyShipManager->getShipStartCoordinates(x, y);
        int segmentIndex = (x - startCords.first) + (y - startCords.second);
        enemyShipManager->attackShip(shipIndex, segmentIndex);
        enemyField[y][x] = CellStatus::ship;
        std::cout << "Hit at (" << x << ", " << y << ")\n";
    }
    else
    {   
        enemyField[y][x] = CellStatus::empty;
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