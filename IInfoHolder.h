#ifndef IINFOHOLDER_H
#define IINFOHOLDER_H

#include "IReader.h"


class IInfoHolder {
public:
    virtual void need() = 0;
    virtual void setReader(IReader* reader) = 0;
    virtual ~IInfoHolder() = default;
};

#endif