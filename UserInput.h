#ifndef USERINPUT_H
#define USERINPUT_H

#include <string>
#include <utility>

class UserInput {
public:
    std::pair<int, int> getCoordinates(const std::string& prompt);
    std::pair<int, int> getFieldSize();
    char getShipOrientation();
    int getInt(const std::string& prompt);
    
private: 
    void clearInput();
};

#endif