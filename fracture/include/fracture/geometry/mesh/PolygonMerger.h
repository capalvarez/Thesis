#ifndef THESIS_POLYGONMERGER_H
#define THESIS_POLYGONMERGER_H

#include <x-poly/models/polygon/Polygon.h>

class PolygonMerger{
public:
    virtual Polygon mergePolygons(Polygon p1, Polygon p2, std::vector<Point> points) = 0;
    virtual Polygon mergePolygons(std::vector<Polygon> polygons, std::vector<Point> points) = 0;
};

#endif 
