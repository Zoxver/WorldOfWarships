#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include <queue>
#include <vector>
#include <stdexcept>
#include "IAbility.h"

class GameField;

class AbilityManager 
{
private:
    GameField& field;
    std::queue<IAbility*> abilityQueue;
    std::vector<IAbility*> availableAbilities;
    std::unordered_map<std::string, int> currentParams;

public:
    AbilityManager(GameField& field);
    void setCurrentAbilityParams(const std::unordered_map<std::string, int>& params);
    std::pair<std::string, std::vector<std::string>> getCurrentAbilityParams() const;
    void activateAbility();
    void getRandomAbility();

private:
    void initializeAbilities();
    void fillInitialQueue();
};

#endif