#ifndef THESIS_SIMPLEPOLYGONMERGER_H
#define THESIS_SIMPLEPOLYGONMERGER_H

#include <fracture/geometry/mesh/PolygonMerger.h>
#include <utilities/Pair.h>

class SimplePolygonMerger: public PolygonMerger{
public:
    Polygon mergePolygons(Polygon p1, Polygon p2, std::vector<Point> points);
    Polygon mergePolygons(std::vector<int> polygons, std::vector<Point> points, BreakableMesh &mesh);

};

#endif 
