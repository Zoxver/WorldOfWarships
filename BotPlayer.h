#ifndef BOTPLAYER_H
#define BOTPLAYER_H

#include "IPlayer.h"
#include <cstdlib>
#include <ctime>

class BotPlayer : public IPlayer {
public:
    BotPlayer();

    void placeShips(GameField& field, ShipManager& shipManager, GameState& gameState) override;
    bool makeMove(GameField& myField, GameField& enemyField, AbilityManager& abilityManager, GameState& gameState) override;

    ~BotPlayer() override = default;
};

#endif
