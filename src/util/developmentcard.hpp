#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include <string>

namespace ariel {
enum class CardType { MONOPOLY,
                      BUILDING_ROADS,
                      YO_ABUNDANCE,
                      KNIGHT,
                      VICTORY_POINT,
                      NONE };

class DevelopmentCard {
private:
    std::string name;
    std::string description;
    CardType type;
    int knightCount;

public:
    DevelopmentCard() { generateCard(); };
    void generateCard();

    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    CardType getType() const { return type; }
};
} // namespace ariel
#endif