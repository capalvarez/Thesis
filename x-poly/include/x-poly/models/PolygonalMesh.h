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
    void createFromFile(std::string fileName);
    void createFromStream(std::ifstream& ofstream);

    std::vector<Polygon>& getPolygons();
    std::vector<Polygon> getPolygons() const;
    Polygon& getPolygon(int index);
    Polygon getPolygon(int index) const;
    void replacePolygon(int index, Polygon newPolygon);

    void writeElements(std::ofstream& file);
    void update();
    void deformPoint(int point_index, double dX, double dY);

    bool areNeighbours(int poly1, int poly2);
    bool areNeighbours(Polygon poly, int poly2);
    bool polygonsTouch(int poly1, int poly2);
    void getNeighboursBySegments(int poly, UniqueList<int> &neighbours);

    int findContainerPolygon(Point p);
    int findContainerPolygon(Point p, int& last);
    int findContainerPolygon(Point p, int init_polygon, int &last);
    int findContainerPolygonLinear(Point p);

    NeighbourInfo getNeighbour(int poly_index, PointSegment direction);
    NeighbourInfo getNeighbour(int poly_index, PointSegment direction, std::vector<int> &previous);
    int getNeighbourFromCommonVertexSet(PointSegment direction, std::vector<int> vertexSet,
                                            std::vector<int> &previousPolygons, int vertexIndex);
    int getNeighbourFromCommonVertexSet(PointSegment direction, std::vector<int> vertexSet, NeighbourInfo& n);

    Region getRegion() const;
    bool isInDomain(Point p);
    bool isInBorder(Point p);
    void getNeighboursByPoint(int poly, UniqueList<int> &neighbours);
    int numberOfPolygons();
    std::vector<NeighbourInfo> getAllNeighboursInPath(PointSegment direction);
};


#endif

