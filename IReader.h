#ifndef IREADER_H
#define IREADER_H

class IReader {
public:
    virtual void read() = 0;
    virtual ~IReader() = default;
};

#endif