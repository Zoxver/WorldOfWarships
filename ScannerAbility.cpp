#include "ScannerAbility.h"

ScannerAbility::ScannerAbility(GameField& field) : field(field) {}

void ScannerAbility::activate() 
{
    field.printField(false, x, y, x + 2, y + 2);
}

std::string ScannerAbility::getName() const
{
    return "Сканер";
}

std::vector<std::string> ScannerAbility::requiredParams() const
{
    return {"x", "y"};
}
    
void ScannerAbility::setParams(const std::unordered_map<std::string, int>& params)
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