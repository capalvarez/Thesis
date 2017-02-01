#ifndef THESIS_MESH_H
#define THESIS_MESH_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <algorithm>
#include <x-poly/voronoi/structures/EdgeData.h>
#include <x-poly/voronoi/structures/mapdata.h>
#include "../../../../utilities/include/utilities/Pair.h"
#include <unordered_map>
#include <x-poly/voronoi/structures/Neighbours.h>
#include <x-poly/voronoi/structures/SegmentMap.h>
#include <x-poly/models/structures/NeighbourInfo.h>
#include "../../../../utilities/include/utilities/UniqueList.h"
#include "Region.h"

class Mesh {
protected:
    List<Point> points;
    std::vector<Polygon> polygons;
    SegmentMap edges;

    Region region;
public:
    Mesh(std::vector<Point> &p, std::vector<Polygon> &e, SegmentMap s, Region r);
    Mesh(const Mesh& m);
    Mesh();
    ~Mesh();

    List<Point>& getPoints();
    List<Point> getPoints() const;
    std::vector<Polygon>& getPolygons();
    std::vector<Polygon> getPolygons() const;
    SegmentMap& getSegments();
    SegmentMap getSegments() const ;

    void printInFile(std::string fileName);
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

