#include "UserInput.h"
#include <iostream>
#include <limits>

int UserInput::getInt(const std::string& prompt) {
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

std::pair<int, int> UserInput::getCoordinates(const std::string& prompt) {
    int x = getInt(prompt + " Введите координату X: ");
    int y = getInt(prompt + " Введите координату Y: ");
    return {x, y};
}

std::pair<int, int> UserInput::getFieldSize() {
    int width = getInt("Введите ширину поля: ");
    int height = getInt("Введите высоту поля: ");
    return {width, height};
}

char UserInput::getShipOrientation() {
    char orientation;
    while (true) {
        std::cout << "Выберите ориентацию корабля (H - горизонтально, V - вертикально): ";
        std::cin >> orientation;
        orientation = toupper(orientation);

        if (orientation == 'H' || orientation == 'V') {
            clearInput();
            return orientation;
        }

        std::cout << "Ошибка ввода. Введите 'H' для горизонтального или 'V' для вертикального размещения.\n";
        clearInput();
    }
}

void UserInput::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
