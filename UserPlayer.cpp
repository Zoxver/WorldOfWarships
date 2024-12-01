#include "UserPlayer.h"
#include "FieldSizeException.h"
#include "NoAbilitiesException.h"
#include "ShipPlacementException.h"
#include "AttackOutOfBoundsException.h"

UserPlayer::UserPlayer() : attackMadeFlag(false), abilityUsedFlag(false), damageX(1), gameFilename(""), sunkedShips(0) {}

void UserPlayer::dropAllFlags() {
    attackMadeFlag = false;
    abilityUsedFlag = false;
}

void UserPlayer::setSunkedShips(int amount) {
    sunkedShips = amount;
}

int UserPlayer::getSunkedShips() {
    return sunkedShips;
}

void UserPlayer::dropLoadGame() {
    gameFilename = "";
}

void UserPlayer::setupAttackFlag() {
    attackMadeFlag = true;
}

void UserPlayer::setupAbilityFlag() {
    abilityUsedFlag = true;
}

void UserPlayer::setDamageX(int damageX) {
    this->damageX = damageX;
}

std::string UserPlayer::isLoadGame() {
    return gameFilename;
}

void UserPlayer::placeShips(GameField& field, ShipManager& shipManager, GameState& gameState) {
    for (int i = 0; i < shipManager.getShipAmount(); ++i) 
    {   
        bool placed = false;
        while (!placed) {
            try {
                int x, y;
                char orientation;
                std::cout << "Постановка корабля " << i + 1 << " размера " << static_cast<int>(shipManager.getShip(i).getSize()) << std::endl;

                while (true) {
                    std::cout << "Введите координаты начала (x y): ";
                    std::cin >> x >> y;

                    if (std::cin.fail() || x < 0 || y < 0) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Ошибка ввода! Пожалуйста, введите целые положительные числа для координат (x y).\n";
                    } else {
                        break;
                    }
                }

                while (true) {
                    std::cout << "Введите ориентацию корабля (h - горизонтальная, v - вертикальная): ";
                    std::cin >> orientation;

                    if (std::cin.fail() || (std::tolower(orientation) != 'h' && std::tolower(orientation) != 'v')) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Ошибка ввода! Введите 'h' для горизонтальной ориентации или 'v' для вертикальной.\n";
                    } else {
                        break;
                    }
                }

                Ship::Orientation shipOrientation = (std::tolower(orientation) == 'h') ? Ship::Orientation::horizontal : Ship::Orientation::vertical;

                field.placeShip(shipManager.getShip(i), x, y, shipOrientation);
     
                gameState.recordCommand("player", "place_ship", {std::to_string(i), std::to_string(x), std::to_string(y), (shipOrientation == Ship::Orientation::horizontal) ? "H" : "V"});
                placed = true;
            } catch (const ShipPlacementException& e) {
                std::cerr << e.what() << '\n';
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } catch (const std::exception& e) {
                std::cerr << "Ошибка в постановке корабля: " << e.what() << '\n';
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
}

bool UserPlayer::makeMove(GameField& myField, GameField& enemyField, AbilityManager& abilityManager, GameState& gameState) {
    bool endTurn = false;

    while (!endTurn) {
        std::cout << "\nВаши опции:\n";
        std::cout << "1) Атаковать ячейку\n";
        std::cout << "2) Использовать способность\n";
        std::cout << "3) Сохранить игру\n";
        std::cout << "4) Загрузить игру\n";
        std::cout << "5) Вывести своё поле\n";
        std::cout << "6) Вывести поле противника\n";
        std::cout << "7) Вывести доступные способности\n";        
        std::cout << "8) Завершить ход\n";
        std::cout << "9) Выйти в меню\n";

        int choice = 0;

        while (true) {
            std::cout << "Введите ваш выбор (1-9): ";
            std::cin >> choice;

            if (std::cin.fail() || choice < 1 || choice > 9) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный ввод! Пожалуйста, выберите значение от 1 до 9.\n";
            } else {
                break;
            }
        }

        switch (choice) {
            case 1: {
                if (attackMadeFlag) {
                    std::cout << "Вы уже атаковали в этом ходу. Выберите другую опцию.\n";
                } else {
                    int x, y;
                    while (true) {
                        std::cout << "Введите координаты для атаки (x y): ";
                        std::cin >> x >> y;

                        if (std::cin.fail() || x < 0 || y < 0) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Некорректный ввод! Введите неотрицательные числа для координат (x y).\n";
                        } else {
                            break;
                        }
                    }

                    try {
                        if (enemyField.attackCell(x, y, 1 * damageX)) {
                            std::cout << "Есть попадание по этим координатам.\n";
                        } else {
                            std::cout << "Нет попадания по этим координатам.\n";
                        }
                        setupAttackFlag();
                        gameState.recordCommand("player", "attack", {std::to_string(x), std::to_string(y), std::to_string(1 * damageX)});
                        if (damageX != 1) { setDamageX(1); }
                    } catch (const AttackOutOfBoundsException& e) {
                        std::cerr << e.what() << '\n';
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                break;
            }
            case 2: {
                if (abilityUsedFlag) {
                    std::cout << "Вы уже использовали способность в этом ходу. Выберите другую опцию.\n";
                } else {
                    try {
                        abilityManager.activateAbility(gameState, this);
                        setupAbilityFlag();
                    } catch (const NoAbilitiesException& e) {
                        std::cerr << e.what() << '\n';
                    }
                }
                break;
            }
            case 3: {
                std::string saveFileName;
                std::cout << "Введите имя файла для сохранения игры: ";
                std::cin >> saveFileName;

                try {
                    std::vector<std::string> activeFactories = abilityManager.getActiveFactories();
                    gameState.saveToFile(saveFileName, attackMadeFlag, abilityUsedFlag, activeFactories, sunkedShips);
                    std::cout << "Игра успешно сохранена.\n";
                } catch (const std::exception& e) {
                    std::cerr << "Не удалось сохранить игру: " << e.what() << '\n';
                }
                break;
            }
            case 4: {
                std::string loadFileName;
                std::cout << "Введите имя файла для загрузки игры: ";
                std::cin >> loadFileName;

                try {
                    gameFilename = loadFileName;
                    std::cout << "Игра успешно загружена.\n";
                    endTurn = true;
                } catch (const std::exception& e) {
                    std::cerr << "Не удалось загрузить игру: " << e.what() << '\n';
                }
                break;
            }
            case 5: {
                std::cout << "Ваше поле:\n";
                myField.printField(false);
                break;
            }
            case 6: {
                std::cout << "Поле противника (без скрытия):\n";
                enemyField.printField();
                break;
            }
            case 7: {
                std::cout << "Доступные способности:\n";
                auto abilities = abilityManager.getActiveFactories();
                for (const auto& ability : abilities) {
                    std::cout << "- " << ability << '\n';
                }
                break;
            }
            case 9: {
                std::cout << "Выход в меню. Ход завершён.\n";
                endTurn = true;
                return true;
            }
            case 8: {
                endTurn = true;
                dropAllFlags();
                break;
            }
            default:
                break;
        }
    }
    return false;
}
