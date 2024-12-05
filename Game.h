#ifndef GAME_H
#define GAME_H

#include "GameField.h"
#include "IPlayer.h"
#include "AbilityManager.h"
#include "CoordReader.h"
#include "CoordHolder.h"
#include "GameState.h"
#include <vector>
#include <limits>


class Game {
private:
    GameField* playerField;
    GameField* botField;
    AbilityManager* playerAbilities;
    ShipManager* playerShips;
    ShipManager* botShips;
    CoordHolder* holder;
    CoordReader* reader;
    IPlayer* player;
    IPlayer* bot;
    GameState gameState;

    bool isGameOver;

    void initialize();
    void setupNewGame();
    void preparePhase(bool skipPlayer = false);

    std::vector<int> getShipSizesFromUser();

    std::pair<int, int> getFieldDimensionsFromUser();

public:
    Game(IPlayer* player, IPlayer* bot);
    Game(IPlayer* player, IPlayer* bot, const std::string& filename);
    ~Game();

    
    void playRound();
    void restartGame();

    bool checkVictory() const;

    bool loadGame(const std::string& filename);
};

#endif
