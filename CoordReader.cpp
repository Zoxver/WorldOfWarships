#include "CoordReader.h"
#include <stdexcept>
#include <iostream>
#include <limits>

CoordReader::CoordReader() : x(0), y(0) {}

int CoordReader::getInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (!std::cin.fail()) {
            return value;
        }

        std::cout << "Ошибка ввода. Пожалуйста, введите целое число.\n";
        clearInput();
    }
}

void CoordReader::read()
{
    int x = getInt("Введите координату X: ");
    int y = getInt("Введите координату Y: ");
    this->x = x;
    this->y = y;
}

void CoordReader::clearInput() 
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int CoordReader::getX() const 
{
    return x;
}

int CoordReader::getY() const 
{
    return y;
}
