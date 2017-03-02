#ifndef THESIS_NEIGHBOURINFO_H
#define THESIS_NEIGHBOURINFO_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>

struct NeighbourInfo {
    int neighbour;
    Point intersection;
    IndexSegment edge;
    bool isEdge;

    NeighbourInfo(int n, IndexSegment e, Point i, bool is){
        neighbour = n;
        edge = e;
        intersection = i;
        isEdge = is;
    }

    void orderCCW(std::vector<Point> points, Point center){
        edge.orderCCW(points, center);
    }
};

#endif 
