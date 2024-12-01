#ifndef DOUBLE_DAMAGE_ABILITY_H
#define DOUBLE_DAMAGE_ABILITY_H

#include "IAbility.h"
#include "GameField.h"
#include "UserPlayer.h"

class DoubleDamageAbility : public IAbility {
public:
    DoubleDamageAbility(GameField& field);
    void activate(GameState& gameState, std::optional<IPlayer*> player) override;
    std::string getName() const override;

private:
    GameField& field;
};

#endif