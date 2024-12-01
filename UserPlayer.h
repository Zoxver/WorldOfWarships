#ifndef USERPLAYER_H
#define USERPLAYER_H

#include "IPlayer.h"
#include <cctype> 
#include <iostream>
#include <limits>

class UserPlayer : public IPlayer {
private:
    bool attackMadeFlag;
    bool abilityUsedFlag;
    int damageX;
    int sunkedShips;
    std::string gameFilename;

public:
    UserPlayer();
    void placeShips(GameField& field, ShipManager& shipManager, GameState& gameState) override;
    bool makeMove(GameField& myField, GameField& enemyField, AbilityManager& abilityManager, GameState& gameState) override;
    void setSunkedShips(int amount);
    int getSunkedShips();
    void dropAllFlags();
    void dropLoadGame();
    void setupAttackFlag();
    void setupAbilityFlag();
    void setDamageX(int damageX);
    std::string isLoadGame();
    ~UserPlayer() override = default;
};

#endif
