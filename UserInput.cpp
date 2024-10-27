#include "UserInput.h"
#include <iostream>

int UserInput::getInt(const std::string& prompt) 
{
    int value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}

std::pair<int, int> UserInput::getCoordinates(const std::string& prompt) 
{
    int x = getInt(prompt + " Введите координату X: ");
    int y = getInt(prompt + " Введите координату Y: ");
    return {x, y};
}
