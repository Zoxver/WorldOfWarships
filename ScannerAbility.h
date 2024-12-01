#ifndef SCANNER_ABILITY_H
#define SCANNER_ABILITY_H

#include "IAbility.h"
#include "GameField.h"

class ScannerAbility : public IAbility {
public:
    ScannerAbility(GameField& field, int x, int y);
    void activate(GameState& gameState, std::optional<IPlayer*> player) override;
    std::string getName() const override;

private:
    GameField& field;
    int x, y;
};

#endif