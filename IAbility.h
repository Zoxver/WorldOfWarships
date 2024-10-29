#ifndef IABILITY_H
#define IABILITY_H

#include <string>
#include <vector>
#include <unordered_map>

class IAbility {
public:
    virtual void activate() = 0;
    virtual std::string getName() const = 0;
    virtual std::vector<std::string> requiredParams() const = 0;
    virtual void setParams(const std::unordered_map<std::string, int>& params) = 0;
    virtual ~IAbility() = default;
};

#endif
