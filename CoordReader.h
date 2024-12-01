#ifndef COORDREADER_H
#define COORDREADER_H

#include "IReader.h"
#include <string>
#include <utility>
#include <stdexcept>

class CoordReader : public IReader {
private:
    int x;
    int y;

public:
    CoordReader();
    void read() override;
    int getInt(const std::string& prompt);
    int getX() const;
    int getY() const;
    ~CoordReader() override = default;

private: 
    void clearInput();
};


#endif