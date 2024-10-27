#ifndef IABILITY_H
#define IABILITY_H

class IAbility {
public:
    virtual void activate() = 0;
    virtual void getParams() = 0;
    virtual ~IAbility() = default;
};

#endif
