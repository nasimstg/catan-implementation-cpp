#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

#include "../board/board.hpp"
#include "../util/developmentcard.hpp"
#include "../util/ResourceType.hpp"
#include "../util/util.hpp"

namespace ariel
{
    class Board;

    class Player
    {
    private:
        std::string p_name;
        int points;
        std::unordered_map<ResourceType, int> resources;
        std::vector<DevelopmentCard> developmentCards;
        std::vector<Road> roads;
        std::vector<Settlement> settlements;
        std::function<void()> endTurnCallBack;
        std::function<const std::vector<Player>&()> getAllPlayersCallback;
        std::function<std::string()> getCurrentPlayerNameCallback;
        std::vector<Player> emptyPlayerVector;
        bool firstTurn;
        bool secondTurn;

    public:
        Player(std::string name = "Player")
            : p_name(name), endTurnCallBack([](){}), getAllPlayersCallback([this](){ return emptyPlayerVector; })
        {
            resources[ResourceType::WOOD] = 0;
            resources[ResourceType::IRON] = 0;
            resources[ResourceType::BRICK] = 0;
            resources[ResourceType::WOOL] = 0;
            resources[ResourceType::OATS] = 0;
            points = 0;
            firstTurn = true;
            secondTurn = false;
        }
        std::string getName() const { return p_name; }
        void placeSettelemnt(Location3d location, Board *board);
        void placeRoad(Location2d location, Board *board, CardType type  = CardType::NONE);
        void rollDice(Board *board);
        void buyDevelopmentCard();
        void useDevelopmentCard(DevelopmentCard card, ResourceType type = ResourceType::NONE, int number = 0, Board *board = nullptr);        void printPoints() const;
        int getPoints() const { return points; };

        void setAllPlayersCallback(std::function<std::vector<Player>()> callback) {
            getAllPlayersCallback = callback;
        }

        const std::vector<Player>& getAllPlayers() {
            if (getAllPlayersCallback) {
                return getAllPlayersCallback();
            } else {
                return emptyPlayerVector;
            }
        }
        
        void setEndTurncallback(std::function<void()> callback){
            endTurnCallBack = callback;
        }
        void endTurn(){
            endTurnCallBack();
        }
        void setGetCurrentPlayerNameCallback(std::function<std::string()> callback) {
            getCurrentPlayerNameCallback = callback;
        }

        std::string getCurrentPlayerName() {
            if (getCurrentPlayerNameCallback) {
                return getCurrentPlayerNameCallback();
            } else {
                return "";
            }
        }
        bool trade(Player& p, ResourceType give, ResourceType get, int amount_give, int amount_get); // Now returns bool
        bool acceptTrade(Player& trader, ResourceType give, ResourceType get, int amount_give, int amount_get);
        void printDevelopmentCards() const;
    };
}

#endif