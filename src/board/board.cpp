#include "./board.hpp"
#include <vector>
#include <time.h>
#include <algorithm>

namespace ariel
{
    void Graph::printGraph()
    {
        for (int i = 0; i < 19; i++)
        {
            std::cout << "Tile " << i << " neighbors: ";
            for (int j = 0; j < 6; j++)
            {
                if (tiles[i].adjecent[j] != nullptr)
                {
                    std::cout << tiles[i].adjecent[j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }
    void Graph::generateGraph()
    {
        // Initialize adjacency list
        tiles[0].adjecent = {nullptr, &tiles[1], &tiles[4], &tiles[3], nullptr, nullptr};
        tiles[1].adjecent = {nullptr, &tiles[0], &tiles[2], &tiles[4], &tiles[5], nullptr};
        tiles[2].adjecent = {nullptr, nullptr, &tiles[6], &tiles[5], &tiles[1], nullptr};
        tiles[3].adjecent = {&tiles[0], &tiles[4], &tiles[8], &tiles[7], nullptr, nullptr};
        tiles[4].adjecent = {&tiles[0], &tiles[5], &tiles[9], &tiles[8], &tiles[3], &tiles[0]};
        tiles[5].adjecent = {&tiles[2], &tiles[6], &tiles[10], &tiles[9], &tiles[4], &tiles[1]};
        tiles[6].adjecent = {nullptr, nullptr, &tiles[11], &tiles[10], &tiles[5], &tiles[2]};
        tiles[7].adjecent = {&tiles[3], &tiles[8], &tiles[12], nullptr, nullptr, nullptr};
        tiles[8].adjecent = {&tiles[4], &tiles[9], &tiles[13], &tiles[12], &tiles[7], &tiles[3]};
        tiles[9].adjecent = {&tiles[5], &tiles[10], &tiles[14], &tiles[13], &tiles[8], &tiles[4]};
        tiles[10].adjecent = {&tiles[6], &tiles[11], &tiles[15], &tiles[14], &tiles[9], &tiles[5]};
        tiles[11].adjecent = {nullptr, nullptr, nullptr, &tiles[15], &tiles[10], &tiles[6]};
        tiles[12].adjecent = {&tiles[8], &tiles[13], &tiles[16], nullptr, nullptr, &tiles[7]};
        tiles[13].adjecent = {&tiles[9], &tiles[14], &tiles[17], &tiles[16], &tiles[12], &tiles[8]};
        tiles[14].adjecent = {&tiles[10], &tiles[15], &tiles[18], &tiles[17], &tiles[13], &tiles[9]};
        tiles[15].adjecent = {&tiles[11], nullptr, nullptr, &tiles[18], &tiles[14], &tiles[10]};
        tiles[16].adjecent = {&tiles[13], &tiles[17], nullptr, nullptr, nullptr, &tiles[12]};
        tiles[17].adjecent = {&tiles[14], &tiles[18], nullptr, nullptr, &tiles[16], &tiles[13]};
        tiles[18].adjecent = {&tiles[15], nullptr, nullptr, nullptr, &tiles[17], &tiles[14]};
    }
    void Board::generateMap()
    {

        //      00 01 02
        //    03 04 05 06
        //  07 08 09 10 11
        //    12 13 14 15
        //     16 17 18
        /*
            Neighbors:
            0-> ? 1 4 3 ? ?
            1-> ? 2 5 4 0 ?
            2-> ? ? 6 5 1 ?
            3-> 0 4 8 7 ? ?
            4-> 1 5 9 8 3 0
            5-> 2 6 10 9 4 1
            6-> ? ? 11 10 5 2
            7-> 3 8 12 ? ? ?
            8-> 4 9 13 12 7 3
            9-> 5 10 14 13 8 4
            10-> 6 11 15 14 9 5
            11-> ? ? ? 15 10 6
            12-> 8 13 16 ? ? 7
            13-> 9 14 17 16 12 8
            14-> 10 15 18 17 13 9
            15-> 11 ? ? 18 14 10
            16-> 13 17 ? ? ? 12
            17-> 14 18 ? ? 16 13
            18-> 15 ? ? ? 17 14
        */
        // 4 forest->wood, 4 Hills->brick, 4 Pasture Land->wool, 3 Aricultural Land->oats, 3 Mountains-> iron
        // 1 Desert->none
        /*
        map[0] = generateTile();
        map[1] = generateTile();
        map[2] = generateTile();
        map[3] = generateTile();
        map[4] = generateTile();
        map[5] = generateTile();
        map[6] = generateTile();
        Tile t; t.type = "Desert"; t.resource = ResourceType::NONE; t.number = 7;
        map[7] = t;
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

        std::vector<int> numbers = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
        std::vector<int> done;
        for(auto n : numbers) {
            srand(time(0));
            int r = rand() % 19;
            while(map[r].number != 0) {
                r = rand() % 19;
            }
            map[r].number = n;
            done.push_back(r);
        }
        */

        // Testing without random
        Tile t;
        t.type = "Forest";
        t.resource = ResourceType::WOOD;
        t.number = 2;
        map[0] = t;
        t.type = "Hills";
        t.resource = ResourceType::BRICK;
        t.number = 3;
        map[1] = t;
        t.type = "Pasture Land";
        t.resource = ResourceType::WOOL;
        t.number = 3;
        map[2] = t;
        t.type = "Agricultural Land";
        t.resource = ResourceType::OATS;
        t.number = 4;
        map[3] = t;
        t.type = "Mountains";
        t.resource = ResourceType::IRON;
        t.number = 4;
        map[4] = t;
        t.type = "Forest";
        t.resource = ResourceType::WOOD;
        t.number = 5;
        map[5] = t;
        t.type = "Hills";
        t.resource = ResourceType::BRICK;
        t.number = 5;
        map[6] = t;
        t.type = "Desert";
        t.resource = ResourceType::NONE;
        t.number = 7;
        map[7] = t;
        t.type = "Pasture Land";
        t.resource = ResourceType::WOOL;
        t.number = 6;
        map[8] = t;
        t.type = "Agricultural Land";
        t.resource = ResourceType::OATS;
        t.number = 6;
        map[9] = t;
        t.type = "Mountains";
        t.resource = ResourceType::IRON;
        t.number = 8;
        map[10] = t;
        t.type = "Forest";
        t.resource = ResourceType::WOOD;
        t.number = 8;
        map[11] = t;
        t.type = "Hills";
        t.resource = ResourceType::BRICK;
        t.number = 9;
        map[12] = t;
        t.type = "Pasture Land";
        t.resource = ResourceType::WOOL;
        t.number = 9;
        map[13] = t;
        t.type = "Agricultural Land";
        t.resource = ResourceType::OATS;
        t.number = 10;
        map[14] = t;
        t.type = "Mountains";
        t.resource = ResourceType::IRON;
        t.number = 10;
        map[15] = t;
        t.type = "Forest";
        t.resource = ResourceType::WOOD;
        t.number = 11;
        map[16] = t;
        t.type = "Hills";
        t.resource = ResourceType::BRICK;
        t.number = 11;
        map[17] = t;
        t.type = "Pasture Land";
        t.resource = ResourceType::WOOL;
        t.number = 12;
        map[18] = t;

        std::cout << &map[0] << std::endl;
        std::cout << &map[1] << std::endl;
        std::cout << &map[2] << std::endl;

        // tileGraph.generateGraph();
        map[0].adjecent = {nullptr, &map[1], &map[4], &map[3], nullptr, nullptr};
        map[1].adjecent = {nullptr, &map[0], &map[2], &map[4], &map[5], nullptr};
        map[2].adjecent = {nullptr, nullptr, &map[6], &map[5], &map[1], nullptr};
        map[3].adjecent = {&map[0], &map[4], &map[8], &map[7], nullptr, nullptr};
        map[4].adjecent = {&map[0], &map[5], &map[9], &map[8], &map[3], &map[0]};
        map[5].adjecent = {&map[2], &map[6], &map[10], &map[9], &map[4], &map[1]};
        map[6].adjecent = {nullptr, nullptr, &map[11], &map[10], &map[5], &map[2]};
        map[7].adjecent = {&map[3], &map[8], &map[12], nullptr, nullptr, nullptr};
        map[8].adjecent = {&map[4], &map[9], &map[13], &map[12], &map[7], &map[3]};
        map[9].adjecent = {&map[5], &map[10], &map[14], &map[13], &map[8], &map[4]};
        map[10].adjecent = {&map[6], &map[11], &map[15], &map[14], &map[9], &map[5]};
        map[11].adjecent = {nullptr, nullptr, nullptr, &map[15], &map[10], &map[6]};
        map[12].adjecent = {&map[8], &map[13], &map[16], nullptr, nullptr, &map[7]};
        map[13].adjecent = {&map[9], &map[14], &map[17], &map[16], &map[12], &map[8]};
        map[14].adjecent = {&map[10], &map[15], &map[18], &map[17], &map[13], &map[9]};
        map[15].adjecent = {&map[11], nullptr, nullptr, &map[18], &map[14], &map[10]};
        map[16].adjecent = {&map[13], &map[17], nullptr, nullptr, nullptr, &map[12]};
        map[17].adjecent = {&map[14], &map[18], nullptr, nullptr, &map[16], &map[13]};
        map[18].adjecent = {&map[15], nullptr, nullptr, nullptr, &map[17], &map[14]};
    }
    void Board::printAdjecency()
    {
        for (int i = 0; i < 19; i++)
        {
            std::cout << "Tile " << i << " neighbors: ";
            for (int j = 0; j < 6; j++)
            {
                if (map[i].adjecent[j] != nullptr)
                {
                    std::cout << map[i].adjecent[j]->number << " ";
                }
            }
            std::cout << std::endl;
        }
    }
    Tile Board::generateTile()
    {
        Tile t;
        std::string type;
        ResourceType resource;
    // Generate Random Type
    sw:
        int r = rand() % 5;
        switch (r)
        {
        case 0:
            type = "Forest";
            resource = ResourceType::WOOD;
            c_w++;
            if (c_w > 4)
            {
                goto sw;
            }
            break;
        case 1:
            type = "Hills";
            resource = ResourceType::BRICK;
            c_b++;
            if (c_b > 4)
                goto sw;
            break;
        case 2:
            type = "Pasture Land";
            resource = ResourceType::WOOL;
            c_wo++;
            if (c_wo > 4)
                goto sw;
            break;
        case 3:
            type = "Agricultural Land";
            resource = ResourceType::OATS;
            c_o++;
            if (c_o > 3)
                goto sw;
            break;
        case 4:
            type = "Mountains";
            resource = ResourceType::IRON;
            c_i++;
            if (c_i > 3)
                goto sw;
            break;
        default:
            type = "Desert";
            resource = ResourceType::NONE;
            break;
        }
        t.type = type;
        t.number = 0;
        t.resource = resource;
        return t;
    }
    void Board::printMap()
    {
        for (int i = 0; i < 19; i++)
        {
            std::cout << "Tile " << i << " type: " << map[i].type << " resource: " << (int)map[i].resource << " number: " << map[i].number << std::endl;
        }
    }
    void Board::printGraph()
    {
        tileGraph.printGraph();
    }
    bool Board::isFree(Location3d loc)
    {
        for (Settlement s : settlements_A)
        {
            if (
                ((loc.x == s.loc.x || loc.x == s.loc.y || loc.x == s.loc.z) &&
                 (loc.y == s.loc.x || loc.y == s.loc.y || loc.y == s.loc.z)) ||
                ((loc.x == s.loc.x || loc.x == s.loc.y || loc.x == s.loc.z) &&
                 (loc.z == s.loc.x || loc.z == s.loc.y || loc.z == s.loc.z)) ||
                ((loc.z == s.loc.x || loc.z == s.loc.y || loc.z == s.loc.z) &&
                 (loc.y == s.loc.x || loc.y == s.loc.y || loc.y == s.loc.z)))
            {
                return false;
            }
        }
        return true;
    }

    bool Board::isFree(Location2d loc)
    {
        Tile t = getTile(loc.x);

        bool isAdjecent = false;
        // Check if x and y are adjecent
        for (auto t : t.adjecent)
        {
            if (t != nullptr)
            {
                if (t->number == loc.y)
                {
                    isAdjecent = true;
                    break;
                }
            }
        }

        if (!isAdjecent)
        {
            return false;
        }

        for (Road r : roads_A)
        {
            for (Location2d l : r.segments)
            {
                if ((l.x == loc.x && l.y == loc.y) || (l.x == loc.y && l.y == loc.x))
                {
                    return false;
                }
            }
        }
        return true;
    }

    void Board::addSettlement(Settlement s)
    {
        settlements_A.push_back(s);
    }
    void Board::addRoad(Road r)
    {
        roads_A.push_back(r);
    }
    void Board::updateSettlement(Settlement s)
    {
        for (size_t i = 0; i < settlements_A.size(); i++)
        {
            if (settlements_A[i].loc.x == s.loc.x && settlements_A[i].loc.y == s.loc.y && settlements_A[i].loc.z == s.loc.z)
            {
                settlements_A[i] = s;
                return;
            }
        }
    }
}