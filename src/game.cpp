#include "./catan/catan.hpp"
#include "./board/board.hpp"
#include "./player/player.hpp"

using namespace ariel;
using namespace std;

int main(){
    Catan c = Catan(Player("Alice"), Player("Bob"), Player("Charlie"));
    c.ChooseStartingPlayer();

    return 0;
}