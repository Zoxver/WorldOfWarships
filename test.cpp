#include <iostream>
#include "Game.h"
#include "UserPlayer.h"
#include "BotPlayer.h"

int main() {
    std::cout << "Выберите тип игрока (1 - Человек, 2 - Бот): ";
    int playerChoice;
    std::cin >> playerChoice;

    IPlayer* player = nullptr;
    IPlayer* bot = new BotPlayer();

    if (playerChoice == 1) {
        player = new UserPlayer();
    } else {
        std::cout << "Ошибка выбора, создается бот." << std::endl;
        player = new BotPlayer(); 
    }


    Game game(player, bot);

    game.playRound();

    delete player;
    delete bot;

    return 0;
}