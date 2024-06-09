#include "./board/board.hpp"
#include "./catan/catan.hpp"
#include "./player/player.hpp"

using namespace ariel;
using namespace std;

int main() {
    Player p1 = Player("Alice");
    Player p2 = Player("Bob");
    Player p3 = Player("Charlie");
    Catan c = Catan(p1, p2, p3); // Alice will start the game.

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

    p1.placeSettelemnt(Location3d{2, 4, 4}, &b); // Settlement placed at 2,4,4.
    p1.placeRoad(Location2d{4, 4}, &b);          // Road placed at 4,4.
    p1.printResources();                         // Alice has the following resources: 1 OATS, 0 WOOD, 1 IRON, 0 BRICK, 0 WOOL,
    p2.placeSettelemnt(Location3d{6, 7, 9}, &b); // Settlement placed at 6,7,9.
    p2.placeRoad(Location2d{7, 9}, &b);          // Road placed at 7,9.

    p3.placeSettelemnt(Location3d{6, 9, 9}, &b); // Location is not free

    p3.placeSettelemnt(Location3d{10, 11, 12}, &b); // Settlement placed at 10,11,12.
    p3.placeRoad(Location2d{11, 12}, &b);           // Road placed at 11,12.

    p1.placeSettelemnt(Location3d{5, 7, 8}, &b); // Settlement placed at 5,7,8.
    p1.placeRoad(Location2d{5, 8}, &b);          // Road placed at 5,8.

    p2.placeSettelemnt(Location3d{8, 8, 10}, &b); // Not your turn

    p1.endTurn();

    p2.placeSettelemnt(Location3d{8, 8, 10}, &b); // Settlement placed at 8,8,10.
    p2.placeRoad(Location2d{8, 10}, &b);          // Road placed at 8,10.

    p1.printResources();                                             // Alice has the following resources: 1 OATS, 1 WOOD, 2 IRON, 0 BRICK, 0 WOOL,
    p2.printResources();                                             // Bob has the following resources: 1 OATS, 0 WOOD, 1 IRON, 1 BRICK, 0 WOOL,
    p2.trade(&p1, ResourceType::IRON, ResourceType::WOOD, 1, 1, &b); // Bob Traded 1 IRON for 1 WOOD with Alice
    p1.printResources();                                             // Alice has the following resources: 1 OATS, 0 WOOD, 3 IRON, 0 BRICK, 0 WOOL,
    p2.printResources();                                             // Bob has the following resources: 1 OATS, 1 WOOD, 0 IRON, 1 BRICK, 0 WOOL,

    p2.updateResources(ResourceType::BRICK, 1); // Bob got 1 IRON
    p2.placeRoad(Location2d{10, 10}, &b);       // Road placed at 10,10. // Multiple roads are connected (Problematic)
    p2.printResources();                        // Bob has the following resources: 2 OATS, 0 WOOD, 1 IRON, 0 BRICK, 0 WOOL,
    p2.endTurn();

    p3.placeSettelemnt(Location3d{9, 9, 11}, &b); // Settlement placed at 9,9,11.
    p3.placeRoad(Location2d{9, 9}, &b);           // Road placed at 9,9.

    p3.endTurn();

    p1.printResources(); // Alice has the following resources: 1 OATS, 0 WOOD, 3 IRON, 0 BRICK, 0 WOOL,
    p2.printResources(); // Bob has the following resources: 2 OATS, 0 WOOD, 1 IRON, 0 BRICK, 0 WOOL,
    p1.rollDice(&b);
    p1.printResources(); // Alice has the following resources: 1 OATS, 0 WOOD, 4 IRON, 0 BRICK, 0 WOOL,
    p2.printResources();

    p1.printPoints();
    p2.printPoints();
    p3.printPoints();
    c.printWinner();
    return 0;
}