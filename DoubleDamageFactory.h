#ifndef DOUBLEDAMAGEFACTORY_H
#define DOUBLEDAMAGEFACTORY_H

#include "IAbilityFactory.h"
#include "GameField.h"

class DoubleDamageFactory : public IAbilityFactory {
private:
    GameField& field;
public:
    DoubleDamageFactory(GameField& field);
    std::string getName() const override;
    IAbility* create(IInfoHolder& baseHolder) override;
};

#endif