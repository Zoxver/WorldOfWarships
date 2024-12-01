#include "BotPlayer.h"
#include "FieldSizeException.h"
#include "NoAbilitiesException.h"
#include "ShipPlacementException.h"
#include "AttackOutOfBoundsException.h"

BotPlayer::BotPlayer() {
    std::srand(std::time(nullptr));
}

void BotPlayer::placeShips(GameField& field, ShipManager& shipManager, GameState& gameState) {
    for (int i = 0; i < shipManager.getShipAmount(); ++i) {
        bool placed = false;

        while (!placed) {
            int x = std::rand() % field.getWidth();
            int y = std::rand() % field.getHeight();
            Ship::Orientation shipOrientation = (std::rand() % 2 == 0 == true) ? Ship::Orientation::horizontal : Ship::Orientation::vertical;

            try {
                field.placeShip(shipManager.getShip(i), x, y, shipOrientation);
                gameState.recordCommand("bot", "place_ship", {std::to_string(i), std::to_string(x), std::to_string(y), (shipOrientation == Ship::Orientation::horizontal) ? "H" : "V"});
                placed = true;
            } catch (const ShipPlacementException& e) {
            }   
        }
    }
}

bool BotPlayer::makeMove(GameField& myField, GameField& enemyField, AbilityManager&, GameState& gameState) {
    bool validAttack = false;

    while (!validAttack) {
        int x = std::rand() % enemyField.getWidth();
        int y = std::rand() % enemyField.getHeight();

        try {
            enemyField.attackCell(x, y);
            gameState.recordCommand("bot", "attack", {std::to_string(x), std::to_string(y)});
            validAttack = true;
        } catch (const AttackOutOfBoundsException& e) {
        }
    }
    return false;
}
