#include "player.hpp"
#include "../board/board.hpp"
#include "../catan/catan.hpp"
#include <iostream>

namespace ariel {
void Player::placeSettelemnt(Location3d location, Board *board) {
    Player *p = catan->current;
    if (this->p_name != p->getName()) {
        std::cout << "Not your turn" << std::endl;
        return;
    }
    if (board->isFree(location)) {

        if (!firstTurn && !secondTurn) {
            if (resources[ResourceType::WOOD] < 1 || resources[ResourceType::IRON] < 1 || resources[ResourceType::BRICK] < 1 || resources[ResourceType::WOOL] < 1) {
                std::cout << "Not enough resources to place a settlement" << std::endl;
                return;
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
    } else {
        std::cout << "Location is not free" << std::endl;
    }
}
void Player::placeRoad(Location2d location, Board *board, CardType type) {
    Player *p = catan->current;
    if (this->p_name != p->getName()) {
        std::cout << "Not your turn" << std::endl;
        return;
    }

    if ((this->resources[ResourceType::WOOD] >= 1 && this->resources[ResourceType::BRICK] >= 1) || firstTurn || secondTurn) {

        if (board->isFree(location)) {
            bool roadPlaced = false;
            for (auto s : this->settlements) {
                /*
                    sx, sy, sz is the location of a settelment s
                    and rx, ry is the location of a road r
                    if pair(rx, ry) == sx, sy || sx, sz || sy, sz then road can be placed
                */
                bool isCloseToSettlement = false;
                bool isCloseToRoad = false;
                bool possibleRoadSegment = false;

                if ((location.x == s.loc.x || location.x == s.loc.y || location.x == s.loc.z) &&
                    (location.y == s.loc.x || location.y == s.loc.y || location.y == s.loc.z)) {
                    isCloseToSettlement = true;
                }

                for (auto r : s.roads) {
                    for (auto t : r.segments) {
                        if ((location.x == t.x || location.x == t.y) && (location.y == t.x || location.y == t.y)) {
                            isCloseToRoad = true;
                            break;
                        }
                    }
                }
                Road road;

                for (auto r : s.roads) {
                    if (r.owner == this) {
                        for (auto t : r.segments) {
                            // Check if loc.x or loc.y is equal to x or y
                            if (location.x == t.x) {
                                Tile tile = board->getTile(t.y);
                                // Check if both t.x and t.y numbered tiles are adjacent to the tile
                                int count = 0;
                                for (auto adj : tile.adjecent) {
                                    if (adj->number == t.x) {
                                        count++;

                                    } else if (adj->number == location.y) {
                                        count++;
                                    }
                                }
                                if (count == 2) {
                                    possibleRoadSegment = true;
                                    break;
                                }
                            } else if (location.x == t.y) {
                                Tile tile = board->getTile(t.x);
                                // Check if both t.x and t.y numbered tiles are adjacent to the tile
                                int count = 0;
                                for (auto adj : tile.adjecent) {
                                    if (adj->number == t.y) {
                                        count++;

                                    } else if (adj->number == location.y) {
                                        count++;
                                    }
                                }
                                if (count == 2) {
                                    possibleRoadSegment = true;
                                    break;
                                }
                            } else if (location.y == t.x) {
                                Tile tile = board->getTile(t.y);
                                // Check if both t.x and t.y numbered tiles are adjacent to the tile
                                int count = 0;
                                for (auto adj : tile.adjecent) {
                                    if (adj->number == t.x) {
                                        count++;

                                    } else if (adj->number == location.x) {
                                        count++;
                                    }
                                }
                                if (count == 2) {
                                    possibleRoadSegment = true;
                                    break;
                                }
                            } else if (location.y == t.y) {
                                Tile tile = board->getTile(t.x);
                                // Check if both t.x and t.y numbered tiles are adjacent to the tile
                                int count = 0;
                                for (auto adj : tile.adjecent) {
                                    if (adj->number == t.y) {
                                        count++;

                                    } else if (adj->number == location.x) {
                                        count++;
                                    }
                                }
                                if (count == 2) {
                                    possibleRoadSegment = true;
                                    break;
                                }
                            }
                        }
                        road = r;
                    }
                }

                if (isCloseToRoad || isCloseToSettlement) {
                    if (type != CardType::BUILDING_ROADS && !firstTurn && !secondTurn) {
                        this->resources[ResourceType::WOOD] -= 1;
                        this->resources[ResourceType::BRICK] -= 1;
                    }
                    if (!possibleRoadSegment) {
                        road.segments.push_back(location);
                        road.owner = this;
                        board->addRoad(road);
                        s.roads.push_back(road);
                        board->updateSettlement(s);
                    }
                    if (possibleRoadSegment) {
                        road.segments.push_back(location);
                        board->addRoad(road);
                        s.roads.pop_back();
                        s.roads.push_back(road);
                        board->updateSettlement(s);
                    }

                    std::cout << "Road placed at " << location.x << "," << location.y << ".\n";
                    if (this->settlements.size() <= 2) {
                        for (auto r : s.roads) {
                            for (auto t : r.segments) {
                                ResourceType type = board->getTile(t.x).resource;
                                if (type != ResourceType::NONE) {
                                    this->resources[type] += 1;
                                }
                                if (t.x == t.y) {
                                    Tile tile = board->getTile(t.x);
                                    ResourceType type = board->getNextTile(tile);
                                    if (type != ResourceType::NONE)
                                        this->resources[type] += 1;
                                } else {
                                    Tile tile = board->getTile(t.y);
                                    ResourceType type = board->getNextTile(tile);
                                    if (type != ResourceType::NONE)
                                        this->resources[type] += 1;
                                }
                            }
                        }
                    }
                    if (secondTurn) {
                        secondTurn = false;
                    }

                    if (firstTurn) {
                        firstTurn = false;
                        secondTurn = true;
                        endTurn();
                    }
                    roadPlaced = true;
                    return;
                }
            }
            if (!roadPlaced)
                std::cout << "Road Has to be connected to a Setterment or Road " << std::endl;
        } else {
            std::cout << "Cannot place road here" << std::endl;
        }
    } else {
        std::cout << "Not enough resources" << std::endl;
    }
};

void Player::rollDice(Board *board) {
    Player *p = catan->current;
    if (this->p_name != p->getName()) {
        std::cout << "Not your turn" << std::endl;
        return;
    }

    /*int dice = rand() % 6 + 1 + rand() % 6 + 1; // 2 dice*/
    int dice = 8;
    std::cout << p_name << " rolled " << dice << ".\n";

    if (dice == 7) {
        // Check if any player has more than 7 resources
        // If so, ask the player to discard half of their resources

        for (auto p : this->getAllPlayers()) {
            int total_resources = 0;
            for (auto r : p.resources) {
                total_resources += r.second;
            }

            if (total_resources > 7) {
                int discard = total_resources / 2;
                std::cout << p.getName() << " has more than 7 resources. Discard " << discard << " resources.\n";
                for (auto r : p.resources) {
                    if (discard == 0)
                        break;
                    if (r.second > 0) {
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

    for (auto s : board->getSettlements()) {
        for (auto r : s.roads) {
            for (auto t : r.segments) {

                if (t.x == dice || t.y == dice) {
                    if (s.type == 1) {
                        ResourceType type = board->getTile(dice).resource;
                        s.owner->resources[type] += 1;
                    } else {
                        ResourceType type = board->getTile(dice).resource;
                        s.owner->resources[type] += 2;
                    }
                    if (t.x == t.y) {
                        if (s.type == 1) {
                            ResourceType type = board->getTile(dice).resource;
                            s.owner->resources[type] += 1;
                        } else {
                            ResourceType type = board->getTile(dice).resource;
                            s.owner->resources[type] += 2;
                        }
                    }
                }
            }
        }
    }
    return;
}

bool Player::trade(Player *p, ResourceType give, ResourceType get, int amount_give, int amount_get, Board *board) {
    Player *cp = catan->current;
    if (this->p_name != cp->getName()) {
        std::cout << "Not your turn" << std::endl;
        return false;
    }
    if (this->p_name == p->getName())
        std::cout << "Cannot trade with yourself" << std::endl;
    if (resources[give] < amount_give) {
        std::cout << "Not enough resources to trade" << std::endl;
    }

    if (p->hasResource(get, amount_get)) {
        p->updateResources(give, amount_give);
        p->updateResources(get, -amount_get);
        this->resources[get] += amount_get;
        this->resources[give] -= amount_give;
        std::cout << p_name << " Traded " << amount_give << " " << give << " for " << amount_get << " " << get << " with " << p->getName() << std::endl;
        return true;
    } else {
        std::cout << "Trade failed" << std::endl;
        return false;
    }

    return true;
}

void Player::buyDevelopmentCard(Board *board) {
    Player *p = catan->current;
    if (this->p_name != p->getName()) {
        std::cout << "Not your turn" << std::endl;
        return;
    }

    // iron 1, wool 1, oats 1
    if (resources[ResourceType::IRON] >= 1 && resources[ResourceType::WOOL] >= 1 && resources[ResourceType::OATS] >= 1) {
        resources[ResourceType::IRON] -= 1;
        resources[ResourceType::WOOL] -= 1;
        resources[ResourceType::OATS] -= 1;
        DevelopmentCard card;
        developmentCards.push_back(card);

        if (card.getType() == CardType::VICTORY_POINT) {
            points += 1;
        }
    } else {
        std::cout << "Not enough resources to buy a development card.\n";
    }
}

void Player::useDevelopmentCard(Board *board, DevelopmentCard card, ResourceType type, int number) {
    Player *p = catan->current;
    if (this->p_name != p->getName()) {
        std::cout << "Not your turn" << std::endl;
        return;
    }

    if (developmentCards.size() == 0) {
        std::cout << "No development cards to use.\n";
        return;
    }
    // check if the player has the card
    bool has_card = false;
    for (auto c : developmentCards) {
        if (c.getType() == card.getType()) {
            has_card = true;
            break;
        }
    }

    if (!has_card) {
        std::cout << "Player does not have the card.\n";
        return;
    }

    if (card.getType() == CardType::KNIGHT) {
        // If has the largest army, get 2 points
        int largest_army = 0;
        for (DevelopmentCard c : this->developmentCards) {
            if (c.getType() == CardType::KNIGHT) {
                largest_army += 1;
            }
            if (largest_army >= 3) {
                points += 2;
            }
        }
        endTurn();
    } else if (card.getType() == CardType::BUILDING_ROADS) {
        // Build 2 roads
        std::cout << "You can build 2 roads.\n";
        std::cout << "Enter the location of the first road.\n";
        int x, y;
        // listen for std::out stream

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
        endTurn();
    } else if (card.getType() == CardType::MONOPOLY) {
        std::cout << "Enter the resource you want to monopolize.\n";
        int r;
        std::cin >> r;
        ResourceType resource = static_cast<ResourceType>(r);
        int total = 0;
        for (Player p : this->getAllPlayers()) {
            if (p.getName() == this->p_name)
                continue;
            total += p.resources[resource];
            p.resources[resource] = 0;
        }
        this->resources[resource] += total;
    } else if (card.getType() == CardType::YO_ABUNDANCE) {
        std::cout << "Enter the resource you want to get.\n";
        int r;
        std::cin >> r;
        ResourceType resource = static_cast<ResourceType>(r);
        this->resources[resource] += 2;
    }
}

void Player::printPoints() const {
    std::cout << p_name << " has " << points << " points.\n";
}

void Player::printDevelopmentCards() const {
    for (auto c : developmentCards) {
        std::cout << c.getName() << " " << c.getDescription() << std::endl;
    }
}
void Player::endTurn() {
    size_t index;
    for (index = 0; index < catan->players.size(); index++) {
        if (catan->players[index]->getName() == this->p_name) {
            break;
        }
    }
    if (index == 0)
        catan->current = catan->players[1];
    else if (index == 1)
        catan->current = catan->players[2];
    else if (index == 2)
        catan->current = catan->players[0];
}
void Player::printResources() const {
    std::cout << p_name << " has the following resources: ";
    for (auto r : resources) {
        std::cout << r.second << " " << r.first << ", ";
    }
    std::cout << std::endl;
}
bool Player::hasResource(ResourceType type, int amount) {
    return resources.at(type) >= amount;
}

void Player::updateResources(ResourceType type, int amount) {
    resources[type] += amount;
}

}; // namespace ariel