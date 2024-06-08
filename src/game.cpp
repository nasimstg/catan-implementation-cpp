#include "./board/board.hpp"
#include "./catan/catan.hpp"
#include "./player/player.hpp"

using namespace ariel;
using namespace std;

int main() {
    Player p1 = Player("Alice");
    Player p2 = Player("Bob");
    Player p3 = Player("Charlie");
    Catan c = Catan(p1, p2, p3);

    Board b = c.getBoard();
    /*b.printMap();
    cout << endl;
    b.printAdjecency();*/

    /*
               00 01 02
              03 04 05 06
             07 08 09 10 11
              12 13 14 15
                16 17 18

                02 03 03
               04 04 05 05
              06 06 07 08 08
               09 09 10 10
                11 11 12
    */

    p1.placeSettelemnt(Location3d{2, 4, 4}, &b);
    p1.placeRoad(Location2d{4, 4}, &b);

    p2.placeSettelemnt(Location3d{6, 7, 9}, &b);
    p2.placeRoad(Location2d{7, 9}, &b);

    p3.placeSettelemnt(Location3d{6, 9, 9}, &b);

    p3.placeSettelemnt(Location3d{10, 11, 12}, &b);
    p3.placeRoad(Location2d{11, 12}, &b);

    p1.placeSettelemnt(Location3d{5, 7, 8}, &b);
    p1.placeRoad(Location2d{5, 8}, &b);

    p1.printPoints();
    p2.printPoints();
    p3.printPoints();
    c.printWinner();
    return 0;
}