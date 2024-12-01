#ifndef COORDHOLDER_H
#define COORDHOLDER_H

#include "IInfoHolder.h"
#include "CoordReader.h"

class CoordHolder : public IInfoHolder {
private:
    int x;
    int y;
    CoordReader* reader;

public:
    CoordHolder();
    void need() override;
    void setReader(IReader* reader) override;
    int getX() const;
    int getY() const;
    ~CoordHolder() override = default;
};

#endif
