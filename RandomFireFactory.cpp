#include "RandomFireFactory.h"
#include "RandomFireAbility.h"

RandomFireFactory::RandomFireFactory(GameField& field) : field(field) {}

IAbility* RandomFireFactory::create(IInfoHolder& holder) {
    return new RandomFireAbility(field);
}

std::string RandomFireFactory::getName() const {
    return "RandomFire";
}