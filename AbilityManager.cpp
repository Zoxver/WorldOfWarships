#include "AbilityManager.h"
#include "DoubleDamageFactory.h"
#include "ScannerFactory.h"
#include "RandomFireFactory.h"
#include "AttackOutOfBoundsException.h"
#include "FieldSizeException.h"
#include "NoAbilitiesException.h"
#include "ShipPlacementException.h"
#include <random>
#include <algorithm>

AbilityManager::AbilityManager(GameField& field, IInfoHolder& infoHolder, IReader& reader, IPlayer* player) : field(field), infoHolder(infoHolder)
{
    infoHolder.setReader(&reader);

    factories = {
        new DoubleDamageFactory(field),
        new ScannerFactory(field),
        new RandomFireFactory(field)
    };

    fillInitialQueue();
}

AbilityManager::AbilityManager(const AbilityManager& other) : field(other.field), infoHolder(other.infoHolder), factories(other.factories), abilityQueue(other.abilityQueue) {}

AbilityManager& AbilityManager::operator=(const AbilityManager& other) {
    if (this != &other) {
        field = other.field;
        infoHolder = other.infoHolder;
        factories = other.factories;
        abilityQueue = other.abilityQueue;
    }

    return *this;
}


void AbilityManager::fillInitialQueue() 
{
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(factories.begin(), factories.end(), rng);

    for (IAbilityFactory* abilityFactory : factories) {
        abilityQueue.push(abilityFactory);
    }
}

void AbilityManager::getRandomAbility() 
{
    int randomIndex = rand() % factories.size();
    IAbilityFactory* newAbility = factories[randomIndex];
    abilityQueue.push(newAbility);
}

void AbilityManager::activateAbility(GameState& gameState, IPlayer* player) {
    if (abilityQueue.empty())
    {
        throw NoAbilitiesException();
    }

    IAbilityFactory* factory = abilityQueue.front();
    IAbility* ability = factory->create(infoHolder);
    
    ability->activate(gameState, player);
    abilityQueue.pop();
}

std::vector<std::string> AbilityManager::getActiveFactories() const {
    std::vector<std::string> activeFactories;
    std::queue<IAbilityFactory*> tempQueue = abilityQueue;

    while (!tempQueue.empty()) {
        IAbilityFactory* factory = tempQueue.front();
        tempQueue.pop();
        activeFactories.push_back(factory->getName());
    }

    return activeFactories;
}

void AbilityManager::loadFactories(const std::vector<std::string>& factoryNames) {
    while (!abilityQueue.empty()) {
        abilityQueue.pop();
    }

    for (const auto& name : factoryNames) {
        bool factoryFound = false;

        for (IAbilityFactory* factory : factories) {
            if (factory->getName() == name) {
                abilityQueue.push(factory);
                factoryFound = true;
                break;
            }
        }

        if (!factoryFound) {
            std::cout << ("Unknown factory: " + name) << '\n';
        }
    }
}
