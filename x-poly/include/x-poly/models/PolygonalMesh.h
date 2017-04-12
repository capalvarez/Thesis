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
    void update();
    void deformPoint(int point_index, double dX, double dY);

    bool areNeighbours(int poly1, int poly2);
    bool areNeighbours(Polygon poly, int poly2);
    bool polygonsTouch(int poly1, int poly2);
    void getAllNeighbours(int poly, UniqueList<int> &neighbours);

    int findContainerPolygon(Point p);
    int findContainerPolygon(Point p, int& last);
    int findContainerPolygon(Point p, int init_polygon, int &last);

    NeighbourInfo getNeighbour(int poly_index, PointSegment direction);
    NeighbourInfo getNeighbour(int poly_index, PointSegment direction, std::vector<int> previous);
    int getPolygonInDirection(std::vector<int> index, PointSegment direction);

    Region getRegion() const;
};


#endif

