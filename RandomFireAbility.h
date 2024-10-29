#ifndef RANDOM_FIRE_ABILITY_H
#define RANDOM_FIRE_ABILITY_H

#include "IAbility.h"
#include "GameField.h"

class RandomFireAbility : public IAbility {
public:
    RandomFireAbility(GameField& field);
    void activate() override;
    std::string getName() const override;

private:
    GameField& field;
};

#endif