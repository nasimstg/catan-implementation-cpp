#include "catan.hpp"
#include <iostream>
#include <time.h>

namespace ariel{
    
    void Catan::ChooseStartingPlayer(){
        /*srand(time(NULL));
        int random = rand() % 3;
        startingPlayer = players[random];*/

        startingPlayer = players[0];
        current = startingPlayer;
        std::cout << startingPlayer.getName() << " will start the game.\n";
    }

    Board Catan::getBoard(){
        return board;
    }

    void Catan::printWinner(){
        for(Player p : players){
            if(p.getPoints() >= 10){
                std::cout << p.getName() << " has won the game with " << p.getName() << " points.\n";
                return;
            }
        }
        std::cout << "No player has won the game yet.\n";
    }

    void Catan::endTurn(){
        for(Player p : players){
            if(p.getName() == current.getName()){
                if(p.getName() == players[players.size() - 1].getName()){
                    current = players[0];
                }
                else{
                    current = players[players.size() - 1];
                }
                return;
            }
        }
    }

}