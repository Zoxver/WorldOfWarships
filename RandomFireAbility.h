#ifndef RANDOM_FIRE_ABILITY_H
#define RANDOM_FIRE_ABILITY_H

#include "IAbility.h"
#include "GameField.h"

class RandomFireAbility : public IAbility {
public:
    RandomFireAbility(GameField& field);
    void activate() override;
    std::string getName() const override;
    std::vector<std::string> requiredParams() const override;
    void setParams(const std::unordered_map<std::string, int>& params) override;

private:
    GameField& field;
};

#endif