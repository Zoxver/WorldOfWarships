#ifndef IABILITYFACTORY_H
#define IABILITYFACTORY_H

#include <string>

class IAbility;
class IInfoHolder;

class IAbilityFactory {
public:
    virtual IAbility* create(IInfoHolder& holder) = 0;
    virtual std::string getName() const = 0;
    virtual ~IAbilityFactory() = default;
};

#endif
