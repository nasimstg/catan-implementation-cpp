#ifndef CATAN_HPP
#define CATAN_HPP

#include <vector>
#include "../player/player.hpp"
#include "../board/board.hpp"

namespace ariel
{

    class Catan
    {
    private:
        std::vector<Player> players;
        Board board;
        Player startingPlayer;
        Player current;

    public:
        Catan(Player p1, Player p2, Player p3)
        {
            this->players.push_back(p1);
            this->players.push_back(p2);
            this->players.push_back(p3);

            ChooseStartingPlayer();

            for (Player p : players)
            {
                p.setEndTurncallback([&]()
                                     { this->endTurn(); });
            }
            for (Player &p : players)
            {
                p.setAllPlayersCallback([&]() -> const std::vector<Player> &
                                        { return this->players; });
            }
        }

        void ChooseStartingPlayer();
        Board getBoard();
        void printWinner();
        void setCurrentPlayer(Player p) { this->current = p; }
        void endTurn();
    };
}

#endif