#ifndef THESIS_POLYGONALMESH_H
#define THESIS_POLYGONALMESH_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <algorithm>
#include <x-poly/models/neighbourhood/EdgeData.h>
#include <x-poly/voronoi/structures/mapdata.h>
#include <unordered_map>
#include <x-poly/models/neighbourhood/Neighbours.h>
#include <x-poly/models/neighbourhood/SegmentMap.h>
#include <x-poly/models/structures/NeighbourInfo.h>
#include <x-poly/models/Mesh.h>
#include "Region.h"

class PolygonalMesh : public Mesh{
protected:
    std::vector<Polygon> polygons;
    Region region;
public:
    PolygonalMesh(std::vector<Point> &p, std::vector<Polygon> &e, SegmentMap s, Region r);
    PolygonalMesh(const PolygonalMesh& m);
    PolygonalMesh();
    ~PolygonalMesh();

    std::vector<Polygon>& getPolygons();
    std::vector<Polygon> getPolygons() const;
    Polygon& getPolygon(int index);

    void writeElements(std::ofstream& file);

    bool isInBoundary(Point p);

    bool areNeighbours(int poly1, int poly2);

    int findContainerPolygon(Point p);
    int findContainerPolygon(Point p, int init_polygon);

    NeighbourInfo getNeighbour(int poly_index, PointSegment direction);
    NeighbourInfo getNeighbour(int poly_index, PointSegment direction, int previous);

    Region getRegion() const;
};


#endif
