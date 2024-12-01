#include "DoubleDamageFactory.h"
#include "DoubleDamageAbility.h"

DoubleDamageFactory::DoubleDamageFactory(GameField& field) : field(field) {}

IAbility* DoubleDamageFactory::create(IInfoHolder& holder) {
    return new DoubleDamageAbility(field);
}

std::string DoubleDamageFactory::getName() const {
    return "DoubleDamage";
}