#include "Abilities.h"
#include "UserInput.h"

DoubleDamageAbility::DoubleDamageAbility(GameField& field) : field(field) {}

void DoubleDamageAbility::activate() 
{
    field.attackCell(x, y);
    field.attackCell(x, y);
}

void DoubleDamageAbility::getParams() 
{
    auto [x, y] = UserInput::getCoordinates("Двойной урон:"); 
}

ScannerAbility::ScannerAbility(GameField& field) : field(field) {}

void ScannerAbility::activate() 
{
    field.printField(false, x, y, x + 2, y + 2);
}

void ScannerAbility::getParams() 
{
    auto [x, y] = UserInput::getCoordinates("Сканер:"); 
}

RandomFireAbility::RandomFireAbility(GameField& field) : field(field) {}

void RandomFireAbility::activate() 
{
    field.randomFire();
}

void RandomFireAbility::getParams() {}