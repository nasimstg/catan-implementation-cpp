#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "../board/board.hpp"
#include "../util/ResourceType.hpp"
#include "../util/developmentcard.hpp"
#include "../util/util.hpp"

namespace ariel {
class Board;
class Catan;

class Player {
private:
    std::string p_name;
    int points;
    std::unordered_map<ResourceType, int> resources;
    std::vector<DevelopmentCard> developmentCards;
    std::vector<Road> roads;
    std::vector<Settlement> settlements;
    std::function<const std::vector<Player> &()> getAllPlayersCallback;
    std::vector<Player> emptyPlayerVector;
    bool firstTurn;
    bool secondTurn;
    bool isTurn;

public:
    Catan *catan;
    Player(std::string name = "Player")
        : p_name(name), getAllPlayersCallback([this]() { return emptyPlayerVector; }) {
        resources[ResourceType::WOOD] = 0;
        resources[ResourceType::IRON] = 0;
        resources[ResourceType::BRICK] = 0;
        resources[ResourceType::WOOL] = 0;
        resources[ResourceType::OATS] = 0;
        points = 0;
        firstTurn = true;
        secondTurn = false;
        isTurn = false;
    }
    std::string getName() const { return p_name; }
    void placeSettelemnt(Location3d location, Board *board);
    void placeRoad(Location2d location, Board *board, CardType type = CardType::NONE);
    void rollDice(Board *board);
    void buyDevelopmentCard(Board *board);
    void useDevelopmentCard(Board *board, DevelopmentCard card, ResourceType type = ResourceType::NONE, int number = 0);
    void printPoints() const;
    int getPoints() const { return points; };

    void setAllPlayersCallback(std::function<const std::vector<Player> &()> callback) {
        getAllPlayersCallback = callback;
    }

    const std::vector<Player> &getAllPlayers() {
        if (getAllPlayersCallback) {
            return getAllPlayersCallback();
        } else {
            return emptyPlayerVector;
        }
    }

    void endTurn();

    bool trade(Player *p, ResourceType give, ResourceType get, int amount_give, int amount_get, Board *board); // Now returns bool
    void printDevelopmentCards() const;

    void printResources() const;
    bool hasResource(ResourceType type, int amount);
    void updateResources(ResourceType type, int amount);
};
} // namespace ariel
#endif