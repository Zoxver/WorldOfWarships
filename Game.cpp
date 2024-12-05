#include "Game.h"
#include "UserPlayer.h"
#include <iostream>
#include <stdexcept>
#include <vector>

Game::Game(IPlayer* player, IPlayer* bot) 
    : player(player), bot(bot), isGameOver(false),
      playerField(nullptr), botField(nullptr),
      playerAbilities(nullptr),
      playerShips(nullptr), botShips(nullptr),
      holder(nullptr), reader(nullptr), gameState() {

    holder = new CoordHolder();
    reader = new CoordReader();
    initialize();
}

Game::Game(IPlayer* player, IPlayer* bot, const std::string& filename) 
    : player(player), bot(bot), isGameOver(false),
      playerField(nullptr), botField(nullptr),
      playerAbilities(nullptr),
      playerShips(nullptr), botShips(nullptr),
      holder(nullptr), reader(nullptr), gameState() {

    loadGame(filename);
}

Game::~Game(){
    delete playerField;
    delete botField;
    delete playerAbilities;
    delete playerShips;
    delete botShips;
    delete holder;
    delete reader;
}

void Game::initialize() {
while (true) {
        std::cout << "\nГлавное меню:\n";
        std::cout << "1) Начать новую игру\n";
        std::cout << "2) Загрузить сохранение\n";
        std::cout << "3) Завершить игру\n";
        std::cout << "Введите ваш выбор (1-3): ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                setupNewGame();
                preparePhase();
                return;
            }
            case 2: {
                std::string filename;
                std::cout << "Введите имя файла сохранения: ";
                std::cin >> filename;

                try {
                    if (!loadGame(filename)) {
                        break;
                    }
                    std::cout << "Сохранение успешно загружено.\n";
                    return;
                } catch (const std::exception& e) {
                    std::cerr << "Не удалось загрузить игру: " << e.what() << '\n';
                }
                break;
            }
            case 3: {
                std::cout << "Выход из игры. До свидания!\n";
                isGameOver = true;
                return;
            }
            default:
                std::cout << "Неверный выбор. Пожалуйста, выберите 1, 2 или 3.\n";
                break;
        }
    }
}

void Game::setupNewGame() {
    std::pair<int, int> fieldSize = getFieldDimensionsFromUser();
    playerField = new GameField(fieldSize.first, fieldSize.second);
    botField = new GameField(fieldSize.first, fieldSize.second);

    std::vector<int> shipSizes = getShipSizesFromUser();
    playerShips = new ShipManager(shipSizes.size(), shipSizes);
    botShips = new ShipManager(shipSizes.size(), shipSizes);

    playerAbilities = new AbilityManager(*botField, *holder, *reader, player);

}

void Game::preparePhase(bool skipPlayer) {
    if (!skipPlayer) {
        std::cout << "Фаза подготовки: Расставьте свои корабли.\n";
        player->placeShips(*playerField, *playerShips, gameState);
    }
    

    std::cout << "Бот расставляет свои корабли...\n";
    bot->placeShips(*botField, *botShips, gameState);

    std::cout << "Фаза подготовки завершена.\n";
}

void Game::playRound() {
    if (isGameOver) {
        return;
    }
    while (!isGameOver) {
        std::cout << "Ход игрока:\n";
        if (player->makeMove(*playerField, *botField, *playerAbilities, gameState)) {
            initialize();
        }
        botField->printField();
        botField->printField(false);

        if (!static_cast<UserPlayer*>(player)->isLoadGame().empty()){
            loadGame(static_cast<UserPlayer*>(player)->isLoadGame());
            static_cast<UserPlayer*>(player)->dropLoadGame();
            std::cout << "Загрузили игру из файла\n";
            continue;
        }

        if (static_cast<UserPlayer*>(player)->getSunkedShips() != botShips->getShipsSunked()){
            playerAbilities->getRandomAbility();
            static_cast<UserPlayer*>(player)->setSunkedShips(playerShips->getShipsSunked());
            std::cout << "Вы получили способность\n";
        }

        if (checkVictory()) {
            isGameOver = true;
            break;
        }


        std::cout << "Ход бота:\n";
        bot->makeMove(*botField, *playerField, *playerAbilities, gameState);

        if (checkVictory()) {
            isGameOver = true;
            break;
        }
    }

    if (playerShips->allShipsSunk()) {
        std::cout << "Игра окончена: Победил бот!\n";
        initialize();
    } else if (botShips->allShipsSunk()) {
        std::cout << "Игра окончена: Вы победили!\n";
        restartGame();
    }
}

bool Game::checkVictory() const {
    return playerShips->allShipsSunk() || botShips->allShipsSunk();
}

void Game::restartGame() {
    std::cout << "Начинается новая игра...\n";
    isGameOver = false;
    gameState.dropCommandLog();
    delete botField;
    botField = new GameField(playerField->getWidth(), playerField->getHeight());
    std::vector<int> shipSizes = playerShips->getShipsSizes();
    delete botShips;
    botShips = new ShipManager(shipSizes.size(), shipSizes);
    preparePhase(true);
    std::vector<std::string> abilities = playerAbilities->getActiveFactories();
    delete playerAbilities;
    playerAbilities = new AbilityManager(*botField, *holder, *reader, player);
    playerAbilities->loadFactories(abilities);

    std::cout << "Новая игра началась.\n";
    playRound();
}

std::vector<int> Game::getShipSizesFromUser() {
    int numShips;
    
    while (true) {
        std::cout << "Введите количество кораблей (от 1 до 10): ";
        std::cin >> numShips;

        if (numShips >= 1 && numShips <= 10) {
            break;
        } else {
            std::cout << "Некорректное количество кораблей. Введите от 1 до 10.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::vector<int> shipSizes;
    for (int i = 0; i < numShips; ++i) {
        int size;
        
        while (true) {
            std::cout << "Введите размер корабля #" << (i + 1) << " (от 1 до 4): ";
            std::cin >> size;

            if (size >= 1 && size <= 4) {
                break;
            } else {
                std::cout << "Некорректный размер корабля. Размер должен быть от 1 до 4.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        shipSizes.push_back(size);
    }

    std::vector<std::string> params;
    for (int size : shipSizes) {
        params.push_back(std::to_string(size));
    }
    gameState.recordCommand("all", "set_ships", params);

    return shipSizes;
}

std::pair<int, int> Game::getFieldDimensionsFromUser() {
    int width, height;

    while (true) {
        std::cout << "Введите ширину поля: ";
        std::cin >> width;
        
        if (width > 0) {
            break;
        } else {
            std::cout << "Ширина поля должна быть больше нуля.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    while (true) {
        std::cout << "Введите высоту поля: ";
        std::cin >> height;
        
        if (height > 0) {
            break;
        } else {
            std::cout << "Высота поля должна быть больше нуля.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    gameState.recordCommand("all", "set_field", {std::to_string(width), std::to_string(height)});

    return std::make_pair(width, height);
}


bool Game::loadGame(const std::string& filename) {
    if (!gameState.loadFromFile(filename)) {
        return false;
    }
    std::cout << "Игра загружена из файла: " << filename << "\n";

    bool setFieldFound = false;
    bool setShipsFound = false;

    for (const auto& cmd : gameState.getCommandLog()) {
        if (cmd.operation == "set_field") {
            if (cmd.parameters.size() != 2) {
                std::cerr << "Ошибка: неправильное количество параметров для set_field\n";
                initialize();
            }

            int width = std::stoi(cmd.parameters[0]);
            int height = std::stoi(cmd.parameters[1]);
            delete playerField;
            delete botField;
            playerField = new GameField(width, height);
            botField = new GameField(width, height);

            setFieldFound = true;

        } else if (cmd.operation == "set_ships") {
            if (cmd.parameters.empty()) {
                std::cerr << "Ошибка: неправильное количество параметров для set_ships\n";
                initialize();
            }

            std::vector<int> shipSizes;
            for (const auto& sizeStr : cmd.parameters) {
                shipSizes.push_back(std::stoi(sizeStr));
            }
            delete playerShips;
            delete botShips;
            playerShips = new ShipManager(shipSizes.size(), shipSizes);
            botShips = new ShipManager(shipSizes.size(), shipSizes);

            setShipsFound = true;

        } else {
            break;
        }
    }

    if (!setFieldFound || !setShipsFound) {
        std::cerr << "Ошибка: отсутствуют обязательные операции 'set_field' или 'set_ships'\n";
        initialize();
    }

    playerAbilities = new AbilityManager(*botField, *holder, *reader, player);
    gameState.replayCommands(*player, *bot, *playerField, *botField, 
                             *playerShips, *botShips, 
                             *playerAbilities);
    return true;
}
