#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include "../board/board.hpp"
#include "../util/developmentcard.hpp"

namespace ariel
{
    enum class Resource { WOOD, IRON, BRICK, WOOL, OATS };

    class Player
    {
    private:
        std::string p_name;
        Board board;
        int points;
        std::unordered_map<Resource, int> resources;
        std::vector<DevelopmentCard> developmentCards;

    public:
        Player(std::string name = "Player")
            : p_name(name)
        {
            resources[Resource::WOOD] = 0;
            resources[Resource::IRON] = 0;
            resources[Resource::BRICK] = 0;
            resources[Resource::WOOL] = 0;
            resources[Resource::OATS] = 0;
        }
        std::string getName() const { return p_name; }
        void placeSettelemnt(std::vector<std::string> places, std::vector<int> placesNum, Board board);
        void placeRoad(std::vector<std::string> places, std::vector<int> placesNum, Board board);
        void rollDice();
        void endTurn();
        bool trade(Player p, std::string give, std::string get, int amount_give, int amount_get); // Now returns bool
        void buyDevelopmentCard();
        void printPoints() const;
        int getPoints() const { return points; };
    };
}