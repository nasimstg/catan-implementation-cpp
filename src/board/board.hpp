#pragma once
#include <map>
#include <vector>
#include <string>
#include "../player/player.hpp"


namespace ariel {
    class Player;
    enum class ResourceType { WOOD, BRICK, WOOL, OATS, IRON, NONE };

    struct Tile {
        std::string type;
        ResourceType resource;
        int number;
        Tile *adjacent[6] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    };

    class Board {
    private:
        std::vector<Tile> map;
        std::map<std::pair<std::string, int>, Player*> locations;
        int c_w, c_b, c_wo, c_o, c_i, c_n;

    public:
        Board() {
            map = std::vector<Tile>(19);
            c_w = 0; c_b = 0; c_wo = 0; c_o = 0; c_i = 0; c_n = 0;
            generateMap();
        }

        void generateMap() {
            // 4 forest->wood, 4 Hills->brick, 4 Pasture Land->wool, 3 Aricultural Land->oats, 3 Mountains-> iron
            // 1 Desert->none

            map[0] = generateTile();
            map[1] = generateTile();
            map[2] = generateTile();
            map[3] = generateTile();
            map[4] = generateTile();
            map[5] = generateTile();
            map[6] = generateTile();
            map[7] = { "Desert", ResourceType::NONE, 7 };
            map[8] = generateTile();
            map[9] = generateTile();
            map[10] = generateTile();
            map[11] = generateTile();
            map[12] = generateTile();
            map[13] = generateTile();
            map[14] = generateTile();
            map[15] = generateTile();
            map[16] = generateTile();
            map[17] = generateTile();
            map[18] = generateTile();
        }

        Tile generateTile() {
            Tile t;
            std::string type; ResourceType resource; int number;
            // Generate Random Type
            sw:
            int r = rand() % 5;
            switch(r) {
                case 0: type = "Forest"; resource = ResourceType::WOOD; number = 2; 
                        c_w++; if(c_w > 4){goto sw;}break;
                case 1: type = "Hills"; resource = ResourceType::BRICK; number = 3; 
                        c_b++; if(c_b > 4) goto sw; break;
                case 2: type = "Pasture Land"; resource = ResourceType::WOOL; number = 4; 
                        c_wo++; if(c_wo > 4) goto sw; break;
                case 3: type = "Agricultural Land"; resource = ResourceType::OATS; number = 5; 
                        c_o++;  if(c_o > 3) goto sw;  break;
                case 4: type = "Mountains"; resource = ResourceType::IRON; number = 6; 
                        c_i++; if(c_i > 3)goto sw;    break;
                default: type = "Desert"; resource = ResourceType::NONE; number = 7; break;
            }
            t.type = type;
            t.resource = resource;
            t.number = number;
            return t;
        }
    };
}