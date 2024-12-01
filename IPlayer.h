#ifndef IPLAYER_H
#define IPLAYER_H

class GameState;
class GameField;
class ShipManager;
class AbilityManager;
#include "GameField.h"

class IPlayer {
public:
    virtual void placeShips(GameField& field, ShipManager& shipmanager, GameState& gameState) = 0;
    virtual bool makeMove(GameField& myField, GameField& enemyField, AbilityManager& abilitymanager, GameState& gameState) = 0;

    //virtual void setGameField(GameField* field) = 0;
    //virtual void setShipManager(ShipManager* manager) = 0;

    virtual ~IPlayer() = default;
};

#endif