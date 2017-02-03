#ifndef THESIS_POLYGONALMESH_H
#define THESIS_POLYGONALMESH_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <algorithm>
#include <x-poly/voronoi/structures/EdgeData.h>
#include <x-poly/voronoi/structures/mapdata.h>
#include <x-poly/utilities/Pair.h>
#include <unordered_map>
#include <x-poly/voronoi/structures/Neighbours.h>
#include <x-poly/voronoi/structures/SegmentMap.h>
#include <x-poly/models/structures/NeighbourInfo.h>
#include <x-poly/utilities/List.h>
#include <x-poly/models/mesh/Mesh.h>
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

    bool isInBoundary(Point p);

    bool isFull();
    bool areNeighbours(int poly1, int poly2);
    int findContainerPolygon(Point p);
    int findContainerPolygon(Point p, int init_polygon);
    Polygon& getPolygon(int index);
    NeighbourInfo getNeighbour(int poly_index, Segment<Point> direction);
    NeighbourInfo getNeighbour(int poly_index, Segment<Point> direction, int previous);
    Region getRegion() const;
};


#endif

