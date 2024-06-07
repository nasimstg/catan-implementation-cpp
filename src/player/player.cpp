#include "player.hpp"
#include "../board/board.hpp"
#include <iostream>

namespace ariel
{
    void Player::placeSettelemnt(std::vector<std::string> places, std::vector<int> placesNum, Board board)
    {
        // Implementation depends on Board class
    }

    void Player::placeRoad(std::vector<std::string> places, std::vector<int> placesNum, Board board)
    {
        // Implementation depends on Board class
    }

    void Player::rollDice()
    {
        int dice = rand() % 6 + 1 + rand() % 6 + 1; // 2 dice
        std::cout << p_name << " rolled " << dice << ".\n";
    }

    void Player::endTurn()
    {
        // Implementation depends on game rules
    }

    bool Player::trade(Player p, std::string give, std::string get, int amount_give, int amount_get)
    {
        // Implementation depends on game rules
        return true;
    }

    void Player::buyDevelopmentCard()
    {
        // iron 1, wool 1, oats 1
        if(resources[Resource::IRON] >= 1 && resources[Resource::WOOL] >= 1 && resources[Resource::OATS] >= 1)
        {
            resources[Resource::IRON] -= 1;
            resources[Resource::WOOL] -= 1;
            resources[Resource::OATS] -= 1;
            DevelopmentCard card;
            developmentCards.push_back(card);
        }
        else
        {
            std::cout << "Not enough resources to buy a development card.\n";
        }
    }

    void Player::printPoints() const
    {
        std::cout << p_name << " has " << points << " points.\n";
    }
}