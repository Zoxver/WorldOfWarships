#include "RandomFireAbility.h"

RandomFireAbility::RandomFireAbility(GameField& field) : field(field) {}

void RandomFireAbility::activate() 
{
    field.randomFire();
}

std::string RandomFireAbility::getName() const
{
    return "Обстрел";
}