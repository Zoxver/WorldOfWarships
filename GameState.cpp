#include "GameState.h"
#include "UserPlayer.h"

void GameState::recordCommand(const std::string& who, const std::string& operation, const std::vector<std::string>& parameters) {
    commandLog.push_back({who, operation, parameters});
}

void GameState::saveToFile(const std::string& filename, bool attackMadeFlag, bool abilityUsedFlag, std::vector<std::string> activeFactories, int sunkedShips) {
    auto removeCommand = [this](const std::string& who, const std::string& operation) {
        for (auto it = commandLog.begin(); it != commandLog.end(); ) {
            if (it->who == who && it->operation == operation) {
                it = commandLog.erase(it);
            } else {
                ++it;
            }
        }
    };

    removeCommand("player", "attackMadeFlag");
    removeCommand("player", "abilityUsedFlag");
    removeCommand("player", "sunkedShips");
    removeCommand("player", "set_factories");

    commandLog.push_back({"player", "attackMadeFlag", {std::to_string(attackMadeFlag)}});
    commandLog.push_back({"player", "abilityUsedFlag", {std::to_string(abilityUsedFlag)}});
    commandLog.push_back({"player", "sunkedShips", {std::to_string(sunkedShips)}});

    std::string factoryList;
    for (const auto& factoryName : activeFactories) {
        if (!factoryList.empty()) {
            factoryList += " ";
        }
        factoryList += factoryName;
    }

    recordCommand("player", "set_factories", {factoryList});

    std::ofstream outFile(filename, std::ios::out);
    if (!outFile.is_open()) {
        throw std::runtime_error("Failed to open file for saving game state.");
    }
    outFile << *this;

    outFile.close();
}


bool GameState::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::in);
    if (!inFile.is_open()) {
        std::cerr << "Не удалось загрузиться из этого файла.\n";
        return false;
    }

    inFile >> *this;
    inFile.close();
    return true;
}

void GameState::dropCommandLog() {

    for (auto it = commandLog.begin(); it != commandLog.end(); ++it) {

        if (it->who == "player" && it->operation == "attack") {
            it = commandLog.erase(it);
            --it;
        } 
        else if (it->who == "bot" && it->operation == "place_ship") {
            it = commandLog.erase(it);
            --it;
        }
    }
}



const std::vector<GameState::Command>& GameState::getCommandLog() const {
        return commandLog;
}

void GameState::executeCommand(const Command& cmd, IPlayer& player, IPlayer& bot, 
                               GameField& playerField, GameField& botField, 
                               ShipManager& playerShips, ShipManager& botShips, 
                               AbilityManager& playerAbilities) {
    if (cmd.operation == "place_ship") {
        int shipIndex = std::stoi(cmd.parameters[0]);
        int x = std::stoi(cmd.parameters[1]);
        int y = std::stoi(cmd.parameters[2]);
        Ship::Orientation orientation = (cmd.parameters[3] == "H") ? Ship::Orientation::horizontal : Ship::Orientation::vertical;

        if (cmd.who == "player") {
            playerField.placeShip(playerShips.getShip(shipIndex), x, y, orientation);
        } else if (cmd.who == "bot") {
            botField.placeShip(botShips.getShip(shipIndex), x, y, orientation);
        }
    } else if (cmd.operation == "attack") {
        int x = std::stoi(cmd.parameters[0]);
        int y = std::stoi(cmd.parameters[1]);

        if (cmd.who == "player") {
            botField.attackCell(x, y);
        } else if (cmd.who == "bot") {
            playerField.attackCell(x, y);
        }
    } else if (cmd.operation == "attackMadeFlag" && cmd.parameters[0] == "1") {
        static_cast<UserPlayer&>(player).setupAttackFlag();
    } else if (cmd.operation == "abilityUsedFlag" && cmd.parameters[0] == "1") {
        static_cast<UserPlayer&>(player).setupAbilityFlag();
    } else if (cmd.operation == "sunkedShips") {
        static_cast<UserPlayer&>(player).setSunkedShips(std::stoi(cmd.parameters[0]));
    } else if (cmd.operation == "set_factories") {
        std::vector<std::string> factoryNames = cmd.parameters;
        playerAbilities.loadFactories(factoryNames);
    } else {
        std::cout << "Skip " << cmd.operation << std::endl;
    }
}


void GameState::replayCommands(IPlayer& player, IPlayer& bot, 
                               GameField& playerField, GameField& botField, 
                               ShipManager& playerShips, ShipManager& botShips, 
                               AbilityManager& playerAbilities) {
    for (const auto& cmd : commandLog) {
        executeCommand(cmd, player, bot, playerField, botField, playerShips, botShips, playerAbilities);
    }
}

const char XOR_MASK = 0x5A;

std::ostream& operator<<(std::ostream& os, const GameState& state) {
    std::ostringstream tempStream;
    tempStream << state.commandLog.size() << "\n";

    for (const auto& cmd : state.commandLog) {
        tempStream << cmd.who << " " << cmd.operation;
        for (const auto& param : cmd.parameters) {
            tempStream << " " << param;
        }
        tempStream << "\n";
    }

    std::string data = tempStream.str();
    for (auto& ch : data) {
        ch ^= XOR_MASK;
    }

    os << data;
    return os;
}

std::istream& operator>>(std::istream& is, GameState& state) {
    std::ostringstream tempBuffer;
    tempBuffer << is.rdbuf();
    std::string encryptedData = tempBuffer.str();

    for (auto& ch : encryptedData) {
        ch ^= XOR_MASK;
    }

    std::istringstream decryptedStream(encryptedData);

    size_t logSize;
    decryptedStream >> logSize;
    decryptedStream.ignore();

    state.commandLog.clear();
    for (size_t i = 0; i < logSize; ++i) {
        std::string line;
        std::getline(decryptedStream, line);

        std::istringstream lineStream(line);
        GameState::Command cmd;

        lineStream >> cmd.who >> cmd.operation;

        std::string param;
        while (lineStream >> param) {
            cmd.parameters.push_back(param);
        }

        state.commandLog.push_back(cmd);
    }

    return is;
}
