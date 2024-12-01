#include "DoubleDamageAbility.h"

DoubleDamageAbility::DoubleDamageAbility(GameField& field) : field(field) {}

void DoubleDamageAbility::activate(GameState& gameState, std::optional<IPlayer*> player)
{
    static_cast<UserPlayer*>(*player)->setDamageX(2);
}

std::string DoubleDamageAbility::getName() const
{
    return "Двойной урон";
}