#ifndef CATAN_HPP
#define CATAN_HPP

#include "../board/board.hpp"
#include "../player/player.hpp"
#include <vector>

namespace ariel {

class Catan {
private:
    Board *board;
    Player *startingPlayer;

public:
    std::vector<Player *> players;
    Player *current;
    Catan(){};
    Catan(Player &p1, Player &p2, Player &p3) {
        this->players.push_back(&p1);
        this->players.push_back(&p2);
        this->players.push_back(&p3);

        ChooseStartingPlayer();

        for (Player *p : players) {
            p->catan = this;
            p->setAllPlayersCallback([this]() -> std::vector<Player> {
                std::vector<Player> players_copy;
                for (Player* player : this->players) {
                    players_copy.push_back(*player);
                }
                return players_copy; });
        }

        this->board = new Board();
    }

    void ChooseStartingPlayer();
    Board getBoard();
    void printWinner();
};
} // namespace ariel

#endif