#ifndef BOARD_HPP
#define BOARD_HPP

#include <map>
#include <vector>
#include <string>
#include "../player/player.hpp"
#include <iostream>
#include "../util/ResourceType.hpp"
#include "../util/util.hpp"


namespace ariel {
    class Player;

    struct Tile {
        std::string type;
        ResourceType resource;
        int number;
        std::vector<Tile*> adjecent = std::vector<Tile*>(6, nullptr);
    };


    class Graph {
    public:
        std::vector<Tile> tiles;
        Graph() : tiles(19) { generateGraph();}
        void generateGraph();
        void printGraph();
    };

    class Board {
    private:
        std::vector<Tile> map;
        std::vector<Settlement> settlements_A;
        std::vector<Road> roads_A;
        Graph tileGraph;
        int c_w, c_b, c_wo, c_o, c_i, c_n;

    public:
        Board() {
            map = std::vector<Tile>(19);
            c_w = 0; c_b = 0; c_wo = 0; c_o = 0; c_i = 0; c_n = 0;
            generateMap();
        }

        void generateMap();
        Tile generateTile();
        void printMap();
        void printGraph();
        void printAdjecency();
        bool isFree(Location3d loc);
        bool isFree(Location2d loc);
        void addSettlement(Settlement s);
        void updateSettlement(Settlement s);
        void addRoad(Road r);
        std::vector<Settlement> getSettlements() { return settlements_A; }
        Tile getTile(int i) { return map[i]; }
    };
}
#endif