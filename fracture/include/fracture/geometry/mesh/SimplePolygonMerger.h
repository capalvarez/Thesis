#ifndef THESIS_SIMPLEPOLYGONMERGER_H
#define THESIS_SIMPLEPOLYGONMERGER_H

#include <fracture/geometry/mesh/PolygonMerger.h>
#include <x-poly/utilities/Pair.h>

class SimplePolygonMerger: public PolygonMerger{
private:
    bool isCommonEdge(std::vector<Segment<int>> commonEdges, Segment<int> edge);
    Pair<int> getEndPoints(std::vector<Segment<int>> edges);
public:
    Polygon mergePolygons(Polygon p1, Polygon p2, std::vector<Point> points);
    Polygon mergePolygons(std::vector<Polygon> polygons, std::vector<Point> points);
};

#endif 
