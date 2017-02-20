#ifndef THESIS_POINTHASHER_H
#define THESIS_POINTHASHER_H

#include <iostream>
#include <x-poly/models/basic/Point.h>

struct PointHasher {
    std::size_t operator()(const Point &x) const{
        return std::hash<double>()(x.getX()) ^ std::hash<double>()(x.getY());
    }
};


#endif 
