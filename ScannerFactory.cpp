#include "ScannerFactory.h"
#include "ScannerAbility.h"
#include "CoordHolder.h"

ScannerFactory::ScannerFactory(GameField& field) : field(field) {}

IAbility* ScannerFactory::create(IInfoHolder& baseHolder) {
    CoordHolder& holder = static_cast<CoordHolder&>(baseHolder);
    holder.need();
    return new ScannerAbility(field, holder.getX(), holder.getY());
}

std::string ScannerFactory::getName() const {
    return "Scanner";
}