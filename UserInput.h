#ifndef USERINPUT_H
#define USERINPUT_H

#include <string>
#include <utility>

class UserInput {
public:
    static int getInt(const std::string& prompt);
    static std::pair<int, int> getCoordinates(const std::string& prompt);
};

#endif