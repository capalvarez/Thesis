#ifndef THESIS_NEIGHBOURINFO_H
#define THESIS_NEIGHBOURINFO_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>

struct NeighbourInfo {
    int neighbour;
    Point intersection;
    Segment<int> edge;

    NeighbourInfo(int n, Segment<int> e, Point i){
        neighbour = n;
        edge = e;
        intersection = i;
    }
};

#endif 
