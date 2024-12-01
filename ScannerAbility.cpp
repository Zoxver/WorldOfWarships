#include "ScannerAbility.h"

ScannerAbility::ScannerAbility(GameField& field, int x, int y) : field(field), x(x), y(y) {}

void ScannerAbility::activate(GameState& gameState, std::optional<IPlayer*> player)
{   
    field.printField(false, x, y, x + 2, y + 2);
}

std::string ScannerAbility::getName() const
{
    return "Сканер";
}