#ifndef THESIS_POLYGONMERGER_H
#define THESIS_POLYGONMERGER_H

#include <set>
#include <x-poly/models/polygon/Polygon.h>
#include <fracture/geometry/BreakableMesh.h>

class PolygonMerger{
public:
    virtual Polygon mergePolygons(Polygon p1, Polygon p2, std::vector<Point> points) = 0;
    virtual Polygon mergePolygons(std::set<int> polygons, std::vector<Point> points, BreakableMesh &mesh) = 0;
};

#endif 
