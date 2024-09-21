#include <stdexcept>
#include <iostream>
#include <vector>
#include "Ship.cpp"
#include "ShipManager.cpp"

class GameField {
public:
    enum class CellStatus {
        UNKNOWN,
        EMPTY,
        SHIP
    };

private:
    int width;
    int height;
    std::vector<std::vector<CellStatus>> field;

public:
    GameField(int width, int height) : width(width), height(height) {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Width and height must be positive");
        }
        field = std::vector<std::vector<CellStatus>>(height, std::vector<CellStatus>(width, CellStatus::UNKNOWN));
    }

    GameField(const GameField& other) : width(other.width), height(other.height), field(other.field) {}


    GameField(GameField&& other) : width(other.width), height(other.height), field(std::move(other.field)) {
    }

    GameField& operator=(const GameField& other) {
        if (this != &other) {
            width = other.width;
            height = other.height;
            field = other.field;
        }
        return *this;
    }

    GameField& operator=(GameField&& other) {
        if (this != &other) {
            width = other.width;
            height = other.height;
            field = std::move(other.field);
        }
        return *this;
    }

    void placeShip(const Ship& ship, int x, int y, Ship::Orientation orientation) {
        int size = static_cast<int>(ship.getSize());

        auto isCellFree = [&](int checkX, int checkY) {
            return checkX >= 0 && checkX < width && checkY >= 0 && checkY < height &&
                field[checkY][checkX] == CellStatus::UNKNOWN;
        };

        if (orientation == Ship::Orientation::HORIZONTAL) {
            if (x + size > width || y >= height) {
                throw std::out_of_range("Ship cannot be placed outside the field");
            }

            for (int i = 0; i < size; ++i) {
                if (!isCellFree(x + i, y)) {
                    throw std::invalid_argument("Cell is already occupied");
                }
            }

            for (int i = -1; i <= size; ++i) {
                if (!isCellFree(x + i, y - 1) || !isCellFree(x + i, y + 1) || !isCellFree(x + i, y)) {
                    throw std::invalid_argument("Ship cannot touch another ship");
                }
            }


            for (int i = 0; i < size; ++i) {
                field[y][x + i] = CellStatus::SHIP;
            }
        } else {
            if (y + size > height || x >= width) {
                throw std::out_of_range("Ship cannot be placed outside the field");
            }

            for (int i = 0; i < size; ++i) {
                if (!isCellFree(x, y + i)) {
                    throw std::invalid_argument("Cell is already occupied");
                }
            }

            for (int i = -1; i <= size; ++i) {
                if (!isCellFree(x - 1, y + i) || !isCellFree(x + 1, y + i) || !isCellFree(x, y + i)) {
                    throw std::invalid_argument("Ship cannot touch another ship");
                }
            }

            for (int i = 0; i < size; ++i) {
                field[y + i][x] = CellStatus::SHIP;
            }
        }
    }


    void attack(int x, int y, ShipManager& shipManager) {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("Attack coordinates are out of bounds");
        }
        if (field[y][x] == CellStatus::SHIP) {
           
            std::cout << "Hit at (" << x << ", " << y << ")\n";
            field[y][x] = CellStatus::EMPTY; // Пример изменения статуса
        } else {
            std::cout << "Miss at (" << x << ", " << y << ")\n";
        }
    }

    CellStatus getCellStatus(int x, int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            throw std::out_of_range("Coordinates are out of bounds");
        }
        return field[y][x];
    }
};

int main(){





}
