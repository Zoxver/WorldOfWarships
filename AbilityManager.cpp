#include "AbilityManager.h"
#include "DoubleDamageAbility.h"
#include "RandomFireAbility.h"
#include "ScannerAbility.h"
#include "GameField.h"
#include "AttackOutOfBoundsException.h"
#include "FieldSizeException.h"
#include "NoAbilitiesException.h"
#include "ShipPlacementException.h"
#include <random>
#include <algorithm>

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

void AbilityManager::setCurrentAbilityParams(const std::unordered_map<std::string, int>& params) 
{
    currentParams = params;
}

std::pair<std::string, std::vector<std::string>> AbilityManager::getCurrentAbilityParams() const 
{   
    if (abilityQueue.empty()) 
    {
        throw NoAbilitiesException();
    }
    IAbility* ability = abilityQueue.front();
    std::vector<std::string> params = ability->requiredParams();
    return {ability->getName(), params};
}

void AbilityManager::getRandomAbility() 
{
    int randomIndex = rand() % availableAbilities.size();
    IAbility* newAbility = availableAbilities[randomIndex];
    abilityQueue.push(newAbility);
}

void AbilityManager::activateAbility() {
    if (abilityQueue.empty()) 
    {
        throw NoAbilitiesException();
    }

    IAbility* ability = abilityQueue.front();
    
    ability->setParams(currentParams);
    ability->activate();
    abilityQueue.pop();
}
