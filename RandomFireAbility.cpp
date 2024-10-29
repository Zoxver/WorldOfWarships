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

std::vector<std::string> RandomFireAbility::requiredParams() const
{
    return {};
}
    
void RandomFireAbility::setParams(const std::unordered_map<std::string, int>& params) {}