#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "GameField.h"
#include "ShipManager.h"


class AbilityManager;

class IPlayer;

class GameState {
public:
    class Command {
    public:
        std::string who;
        std::string operation;
        std::vector<std::string> parameters;
    };

private:
    std::vector<Command> commandLog;
    void executeCommand(const Command& cmd, IPlayer& player, IPlayer& bot, 
                               GameField& playerField, GameField& botField, 
                               ShipManager& playerShips, ShipManager& botShips, 
                               AbilityManager& playerAbilities);

public:
    const std::vector<Command>& getCommandLog() const;

    void recordCommand(const std::string& who, const std::string& operation, const std::vector<std::string>& parameters);

    void saveToFile(const std::string& filename, bool attackMadeFlag, bool abilityUsedFlag, std::vector<std::string> activeFactories, int sunkedShips);

    bool loadFromFile(const std::string& filename);

    void replayCommands(IPlayer& player, IPlayer& bot, 
                               GameField& playerField, GameField& botField, 
                               ShipManager& playerShips, ShipManager& botShips, 
                               AbilityManager& playerAbilities);

    void dropCommandLog();

    friend std::ostream& operator<<(std::ostream& os, const GameState& state);
    friend std::istream& operator>>(std::istream& is, GameState& state);
};

#endif
