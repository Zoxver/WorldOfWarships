#ifndef IABILITY_H
#define IABILITY_H

#include <string>
#include <vector>
#include <unordered_map>

class IAbility {
public:
    virtual void activate() = 0;
    virtual std::string getName() const = 0;
    virtual std::vector<std::string> requiredParams() const { return {}; }
    virtual void setParams(const std::unordered_map<std::string, int>& params) {}
    virtual ~IAbility() = default;
};

#endif
