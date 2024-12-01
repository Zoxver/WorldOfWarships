#ifndef RANDOMFIREFACILITY_H
#define RANDOMFIREFACILITY_H

#include "IAbilityFactory.h"
#include "GameField.h"

class RandomFireFactory : public IAbilityFactory {
private:
    GameField& field;
public:
    RandomFireFactory(GameField& field);
    std::string getName() const override;
    IAbility* create(IInfoHolder& baseHolder) override;
};

#endif
