#ifndef SCANNERFACTORY_H
#define SCANNERFACTORY_H

#include "IAbilityFactory.h"
#include "GameField.h"

class ScannerFactory : public IAbilityFactory {
private:
    GameField& field;
public:
    ScannerFactory(GameField& field);
    std::string getName() const override;
    IAbility* create(IInfoHolder& baseHolder) override;
};

#endif
