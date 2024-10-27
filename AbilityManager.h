#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include <queue>
#include <vector>
#include <stdexcept>
#include "IAbility.h"

class GameField;

class AbilityManager {
private:
    GameField& field;
    std::queue<IAbility*> abilityQueue;
    std::vector<IAbility*> availableAbilities;

public:
    AbilityManager(GameField& field);
    void initializeAbilities();
    void fillInitialQueue();
    void getRandomAbility();
    void activateAbility();
};

#endif