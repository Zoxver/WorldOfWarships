#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include <queue>
#include <vector>
#include <stdexcept>
#include "IAbilityFactory.h"
#include "IReader.h"
#include "IInfoHolder.h"
#include "IPlayer.h"
#include "IAbility.h"
#include "GameField.h"
#include "GameState.h"

class AbilityManager 
{
private:
    GameField& field;
    IInfoHolder& infoHolder;
    std::vector<IAbilityFactory*> factories;
    std::queue<IAbilityFactory*> abilityQueue;

public:
    AbilityManager(GameField& field, IInfoHolder& infoHolder, IReader& reader, IPlayer* player);
    AbilityManager(const AbilityManager &other);

    AbilityManager &operator=(const AbilityManager &other);
    void activateAbility(GameState& gameState, IPlayer* player);
    void getRandomAbility();
    std::vector<std::string> getActiveFactories() const;
    void loadFactories(const std::vector<std::string>& factoryNames);

private:
    void fillInitialQueue();
};

#endif