#include "player.hpp"
#include "../board/board.hpp"
#include <iostream>

namespace ariel
{
    void Player::placeSettelemnt(Location3d location, Board *board)
    {
        /*if (getName() != getCurrentPlayerName())
        {
            std::cout << "Not your turn" << std::endl;
            return;
        }*/
        if (board->isFree(location))
        {

            if (!firstTurn && !secondTurn)
            {
                if (resources[ResourceType::WOOD] < 1 || resources[ResourceType::IRON] < 1 || resources[ResourceType::BRICK] < 1 || resources[ResourceType::WOOL] < 1)
                {
                    std::cout << "Not enough resources to place a settlement" << std::endl;
                }
                resources[ResourceType::WOOD] -= 1;
                resources[ResourceType::IRON] -= 1;
                resources[ResourceType::BRICK] -= 1;
                resources[ResourceType::WOOL] -= 1;
            }
            Settlement settlement;
            settlement.loc = location;
            settlement.owner = this;
            settlement.type = 1;
            this->settlements.push_back(settlement);
            board->addSettlement(settlement);
            std::cout << "Settlement placed at " << location.x << "," << location.y << "," << location.z << ".\n";
            this->points += 1;
        }
        else
        {
            std::cout << "Location is not free" << std::endl;
        }
    }
    void Player::placeRoad(Location2d location, Board *board, CardType type)
    {
        /*if (getName() != this->getCurrentPlayerName())
        {
            std::cout << "Not your turn" << std::endl;
            return;
        }*/
        if ((this->resources[ResourceType::WOOD] >= 1 && this->resources[ResourceType::BRICK] >= 1) || firstTurn || secondTurn)
        {

            if (board->isFree(location))
            {
                for (auto s : this->settlements)
                {
                    /*
                        sx, sy, sz is the location of a settelment s
                        and rx, ry is the location of a road r
                        if pair(rx, ry) == sx, sy || sx, sz || sy, sz then road can be placed
                    */
                    bool isCloseToSettlement = false;
                    bool isCloseToRoad = false;

                    if ((location.x == s.loc.x || location.x == s.loc.y || location.x == s.loc.z) &&
                        (location.y == s.loc.x || location.y == s.loc.y || location.y == s.loc.z))
                        isCloseToSettlement = true;
                    for (auto r : s.roads)
                    {
                        for (auto t : r.segments)
                        {
                            if ((location.x == t.x || location.x == t.y) && (location.y == t.x || location.y == t.y))
                            {
                                isCloseToRoad = true;
                                break;
                            }
                        }
                    }
                    if (isCloseToRoad || isCloseToSettlement)
                    {
                        if (type != CardType::BUILDING_ROADS || (!firstTurn && !secondTurn))
                        {
                            this->resources[ResourceType::WOOD] -= 1;
                            this->resources[ResourceType::BRICK] -= 1;
                        }
                        Road road;
                        road.segments.push_back(location);
                        road.owner = this;
                        board->addRoad(road);
                        s.roads.push_back(road);
                        board->updateSettlement(s);
                        std::cout << "Road placed at " << location.x << "," << location.y << ".\n";
                        if (this->settlements.size() < 2)
                        {
                            for (auto r : s.roads)
                            {
                                for (auto t : r.segments)
                                {
                                    ResourceType type = board->getTile(t.x).resource;
                                    this->resources[type] += 1;
                                    type = board->getTile(t.y).resource;
                                    this->resources[type] += 1;
                                }
                            }
                        }
                        if (firstTurn)
                        {
                            firstTurn = false;
                            secondTurn = true;
                            endTurn();
                        }
                        if (secondTurn)
                        {
                            secondTurn = false;
                        }
                        return;
                    }
                    else
                    {
                        std::cout << "Cannot place road here" << std::endl;
                    }
                }
            }
            else
            {
                std::cout << "Cannot place road here" << std::endl;
            }
        }
        else
        {
            std::cout << "Not enough resources" << std::endl;
        }
    };

    void Player::rollDice(Board *board)
    {
        /*if (getName() != this->getCurrentPlayerName())
        {
            std::cout << "Not your turn" << std::endl;
            return;
        }*/
        int dice = rand() % 6 + 1 + rand() % 6 + 1; // 2 dice
        std::cout << p_name << " rolled " << dice << ".\n";

        if (dice == 7)
        {
            // Check if any player has more than 7 resources
            // If so, ask the player to discard half of their resources

            for (auto p : this->getAllPlayers())
            {
                int total_resources = 0;
                for (auto r : p.resources)
                {
                    total_resources += r.second;
                }

                if (total_resources > 7)
                {
                    int discard = total_resources / 2;
                    std::cout << p.getName() << " has more than 7 resources. Discard " << discard << " resources.\n";
                    for (auto r : p.resources)
                    {
                        if (discard == 0)
                            break;
                        if (r.second > 0)
                        {
                            r.second -= 1;
                            discard -= 1;
                        }
                    }
                }
            }
            return;
        }

        // Check if any player has settlements on the tile with the number rolled
        // If settelment type is 1 then add 1 resource of the type of the tile to all the player that have roads[n].x == dice || roads[n].y == dice
        // type 2 settelments get 2 resources

        for (auto s : board->getSettlements())
        {
            for (auto r : s.roads)
            {
                for (auto t : r.segments)
                {
                    if (t.x == dice || t.y == dice)
                    {
                        if (s.type == 1)
                        {
                            ResourceType type = board->getTile(dice).resource;
                            s.owner->resources[type] += 1;
                        }
                        else
                        {
                            ResourceType type = board->getTile(dice).resource;
                            s.owner->resources[type] += 2;
                        }
                    }
                }
            }
        }
    }

    bool Player::trade(Player &p, ResourceType give, ResourceType get, int amount_give, int amount_get)
    {
        if (getName() != this->getCurrentPlayerName())
        {
            std::cout << "Not your turn" << std::endl;
            return false;
        }
        if (this->p_name == p.getName())
            std::cout << "Cannot trade with yourself" << std::endl;
        if (resources[give] < amount_give)
        {
            std::cout << "Not enough resources to trade" << std::endl;
        }

        // Request the other player to accept the trade
        bool accepted = p.acceptTrade(*this, give, get, amount_give, amount_get);

        if (accepted)
        {
            // If the other player accepted, update the resources
            resources[give] -= amount_give;
            resources[get] += amount_get;
        }

        return accepted;
    }

    bool Player::acceptTrade(Player &trader, ResourceType give, ResourceType get, int amount_give, int amount_get)
    {
        if (this->p_name == trader.getName())
            std::cout << "Cannot trade with yourself" << std::endl;

        // Decide whether to accept the trade
        // This could be based on AI or user input
        std::cout << "Player " << trader.getName() << " wants to trade " << amount_give << " " << give << " for " << amount_get << " " << get << ". Do you accept? (yes/no)" << std::endl;
        std::string response;
        std::cin >> response;

        if (response == "yes")
        {
            if (resources[give] < amount_get)
            {
                std::cout << "Not enough resources to trade" << std::endl;
            }

            // Update the resources
            resources[give] -= amount_get;
            resources[get] += amount_give;

            return true;
        }

        return false;
    }

    void Player::buyDevelopmentCard()
    {
        /*if (getName() != this->getCurrentPlayerName())
        {
            std::cout << "Not your turn" << std::endl;
            return;
        }*/
        // iron 1, wool 1, oats 1
        if (resources[ResourceType::IRON] >= 1 && resources[ResourceType::WOOL] >= 1 && resources[ResourceType::OATS] >= 1)
        {
            resources[ResourceType::IRON] -= 1;
            resources[ResourceType::WOOL] -= 1;
            resources[ResourceType::OATS] -= 1;
            DevelopmentCard card;
            developmentCards.push_back(card);

            if (card.getType() == CardType::VICTORY_POINT)
            {
                points += 1;
            }
        }
        else
        {
            std::cout << "Not enough resources to buy a development card.\n";
        }
    }

    void Player::useDevelopmentCard(DevelopmentCard card, ResourceType type, int number, Board *board)
    {
        /*if (getName() != this->getCurrentPlayerName())
        {
            std::cout << "Not your turn" << std::endl;
            return;
        }*/
        if (developmentCards.size() == 0)
        {
            std::cout << "No development cards to use.\n";
            return;
        }
        // check if the player has the card
        bool has_card = false;
        for (auto c : developmentCards)
        {
            if (c.getType() == card.getType())
            {
                has_card = true;
                break;
            }
        }

        if (!has_card)
        {
            std::cout << "Player does not have the card.\n";
            return;
        }

        if (card.getType() == CardType::KNIGHT)
        {
            // If has the largest army, get 2 points
            int largest_army = 0;
            for (DevelopmentCard c : this->developmentCards)
            {
                if (c.getType() == CardType::KNIGHT)
                {
                    largest_army += 1;
                }
                if (largest_army >= 3)
                {
                    points += 2;
                }
            }
        }
        else if (card.getType() == CardType::BUILDING_ROADS)
        {
            // Build 2 roads
            std::cout << "You can build 2 roads.\n";
            std::cout << "Enter the location of the first road.\n";
            int x, y;
            std::cin >> x >> y;
            Location2d location;
            location.x = x;
            location.y = y;
            placeRoad(location, board, CardType::BUILDING_ROADS);

            std::cout << "Enter the location of the second road.\n";
            std::cin >> x >> y;
            location.x = x;
            location.y = y;
            placeRoad(location, board, CardType::BUILDING_ROADS);
        }
        else if (card.getType() == CardType::MONOPOLY)
        {
            std::cout << "Enter the resource you want to monopolize.\n";
            int r;
            std::cin >> r;
            ResourceType resource = static_cast<ResourceType>(r);
            int total = 0;
            for (Player p : this->getAllPlayers())
            {
                if (p.getName() == this->p_name)
                    continue;
                total += p.resources[resource];
                p.resources[resource] = 0;
            }
            this->resources[resource] += total;
        }
        else if (card.getType() == CardType::YO_ABUNDANCE)
        {
            std::cout << "Enter the resource you want to get.\n";
            int r;
            std::cin >> r;
            ResourceType resource = static_cast<ResourceType>(r);
            this->resources[resource] += 2;
        }
        endTurn();
    }

    void Player::printPoints() const
    {
        std::cout << p_name << " has " << points << " points.\n";
    }

    void Player::printDevelopmentCards() const
    {
        for (auto c : developmentCards)
        {
            std::cout << c.getName() << " " << c.getDescription() << std::endl;
        }
    }
}