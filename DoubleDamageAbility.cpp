#include "DoubleDamageAbility.h"

DoubleDamageAbility::DoubleDamageAbility(GameField& field) : field(field) {}

void DoubleDamageAbility::activate() 
{
    field.attackCell(x, y);
    field.attackCell(x, y);
}

std::string DoubleDamageAbility::getName() const
{
    return "Двойной урон";
}

std::vector<std::string> DoubleDamageAbility::requiredParams() const
{
    return {"x", "y"};
}
    
void DoubleDamageAbility::setParams(const std::unordered_map<std::string, int>& params)
{
    if (params.count("x")) 
    {
        x = params.at("x");
    }
    if (params.count("y")) 
    {
        y = params.at("y");
    }
}