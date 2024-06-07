#ifndef UTIL_H
#define UTIL_H
#include <vector>

namespace ariel {
    class Player;
    struct Location3d {
        int x, y, z;
    };

    struct Location2d {
        int x, y;
    };

    struct Road
    {
        Player* owner;
        std::vector<Location2d> segments;
    };

    struct Settlement {
        Player* owner;
        int type;
        Location3d loc;
        std::vector<Road> roads;
    };
}
#endif