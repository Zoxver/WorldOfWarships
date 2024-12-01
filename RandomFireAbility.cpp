#include "RandomFireAbility.h"

RandomFireAbility::RandomFireAbility(GameField& field) : field(field) {}

void RandomFireAbility::activate(GameState& gameState, std::optional<IPlayer*> player) 
{
    std::vector<std::pair<int, int>> shipCells;

    for (int y = 0; y < field.getHeight(); ++y) 
    {
        for (int x = 0; x < field.getWidth(); ++x) 
        {
            if (field.getField()[y][x].getShip()) 
            {
                shipCells.emplace_back(x, y);
            }
        }
    }

    int randomIndex = rand() % shipCells.size();
    int x = shipCells[randomIndex].first;
    int y = shipCells[randomIndex].second;
    field.attackCell(x, y, 1, false);
    gameState.recordCommand("player", "attack", {std::to_string(x), std::to_string(y), std::to_string(1), std::to_string(false)});
}

std::string RandomFireAbility::getName() const
{
    return "Обстрел";
}