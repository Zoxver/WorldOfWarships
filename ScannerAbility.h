#ifndef SCANNER_ABILITY_H
#define SCANNER_ABILITY_H

#include "IAbility.h"
#include "GameField.h"

class ScannerAbility : public IAbility {
public:
    ScannerAbility(GameField& field);
    void activate() override;
    std::string getName() const override;
    std::vector<std::string> requiredParams() const override;
    void setParams(const std::unordered_map<std::string, int>& params) override;

private:
    GameField& field;
    int x, y;
};

#endif