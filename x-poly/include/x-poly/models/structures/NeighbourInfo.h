#ifndef THESIS_NEIGHBOURINFO_H
#define THESIS_NEIGHBOURINFO_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>

struct NeighbourInfo {
    int neighbour;
    Point intersection;
    IndexSegment edge;
    bool isEdge;
    bool isVertex;
    int extraPoint;

    NeighbourInfo(){}

    NeighbourInfo(int n, IndexSegment e, Point i, bool is){
        neighbour = n;
        edge = e;
        intersection = i;
        isEdge = is;
        isVertex = false;
        extraPoint = -1;
    }

    void orderCCW(std::vector<Point> points, Point center){
        edge.orderCCW(points, center);
    }

};

#endif 
