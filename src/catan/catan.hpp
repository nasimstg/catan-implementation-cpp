#include "../player/player.hpp"
#include "../board/board.hpp"
#include <vector>

namespace ariel
{
    class Catan
    {
    private:
        std::vector<Player> players;
        Board board;
        Player startingPlayer;

    public:
        Catan(Player p1, Player p2, Player p3)
        {
            this->players.push_back(p1);
            this->players.push_back(p2);
            this->players.push_back(p3);
        }
        
        void ChooseStartingPlayer();
        Board getBoard();
        void printWinner();
    };
}