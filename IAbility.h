#ifndef IABILITY_H
#define IABILITY_H

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

class GameState;
class IPlayer;


class IAbility {
public:
    virtual void activate(GameState& gameState, std::optional<IPlayer*> player) = 0;
    virtual std::string getName() const = 0;
    virtual ~IAbility() = default;
};

#endif
