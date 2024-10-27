#include "AbilityManager.h"
#include "Abilities.h"
#include "GameField.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

AbilityManager::AbilityManager(GameField& field) : field(field) {
    initializeAbilities();
    fillInitialQueue();
}

void AbilityManager::initializeAbilities() {
    availableAbilities.push_back(new DoubleDamageAbility(field));
    availableAbilities.push_back(new ScannerAbility(field));
    availableAbilities.push_back(new RandomFireAbility(field));
}

void AbilityManager::fillInitialQueue() {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(availableAbilities.begin(), availableAbilities.end(), rng);

    for (IAbility* ability : availableAbilities) {
        abilityQueue.push(ability);
    }
}

void AbilityManager::getRandomAbility() 
{
    int randomIndex = rand() % availableAbilities.size();
    IAbility* newAbility = availableAbilities[randomIndex];
    abilityQueue.push(newAbility);
}

void AbilityManager::activateAbility() {
    if (abilityQueue.empty()) {
        throw std::runtime_error("No abilities available");
    }

    IAbility* ability = abilityQueue.front();
    abilityQueue.pop();

    ability->getParams();
    ability->activate();
}
