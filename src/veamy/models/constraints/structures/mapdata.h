#ifndef MAPDATA_H
#define MAPDATA_H

#include <x-poly/models/basic/Point.h>

struct PointHasher {
    std::size_t operator()(const Point &k) const {
        using std::size_t;
        using std::hash;

        return hash<int>()(k.getX()) + hash<int>()(k.getY());
    }
};

struct intHasher {
    std::size_t operator()(const int &k) const {
        using std::size_t;
        using std::hash;

        return hash<int>()(k);
    }
};

#endif