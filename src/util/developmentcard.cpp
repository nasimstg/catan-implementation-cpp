#include "developmentcard.hpp"

namespace ariel {
void DevelopmentCard::generateCard() {
    int random = rand() % 5;
    switch (random) {
    case 0:
        name = "Monopoly";
        description = "When played, you may take all of one type of resource from all of your opponents.";
        type = CardType::MONOPOLY;
        break;
    case 1:
        name = "Building Roads";
        description = "When played, you may build 2 roads for free.";
        type = CardType::BUILDING_ROADS;
        break;
    case 2:
        name = "Year of Abundance";
        description = "When played, you may take any 2 resources from the bank.";
        type = CardType::YO_ABUNDANCE;
        break;
    case 3:
        name = "Knight";
        description = "When played, you may move the robber to a new hex and steal a resource from a player who has a settlement on that hex.";
        type = CardType::KNIGHT;
        knightCount++;
        break;
    case 4:
        name = "Victory Point";
        description = "When played, you may take 1 victory point.";
        type = CardType::VICTORY_POINT;
        break;
    }
}

} // namespace ariel