#include "CoordHolder.h"
#include <stdexcept>

CoordHolder::CoordHolder() : x(0), y(0), reader(nullptr) {}

void CoordHolder::setReader(IReader* reader) 
{
    this->reader = static_cast<CoordReader*>(reader);
}

void CoordHolder::need() 
{
    if (!reader) {
        throw std::runtime_error("Reader is not set for CoordHolder.");
    }
    reader->read();
    x = reader->getX();
    y = reader->getY();
}

int CoordHolder::getX() const 
{
    return x;
}

int CoordHolder::getY() const 
{
    return y;
}
