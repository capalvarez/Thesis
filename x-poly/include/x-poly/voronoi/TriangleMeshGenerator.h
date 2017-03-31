#ifndef THESIS_TRIANGLEMESHGENERATOR_H
#define THESIS_TRIANGLEMESHGENERATOR_H

#include "MeshGenerator.h"
#include <vector>
#include <x-poly/voronoi/lib/triangle.h>
#include <unordered_map>
#include <x-poly/models/neighbourhood/EdgeData.h>
#include <x-poly/voronoi/structures/PointData.h>
#include "../../../../utilities/include/utilities/UniqueList.h"
#include <x-poly/models/Region.h>
#include <x-poly/voronoi/structures/mapdata.h>
#include <x-poly/models/Triangulation.h>
#include <x-poly/models/Triangulation.h>
#include <x-poly/models/neighbourhood/Neighbours.h>
#include <x-poly/models/neighbourhood/SegmentMap.h>

class TriangleMeshGenerator : public MeshGenerator{
private:
    Region region;
    PolygonalMesh mesh;

    std::vector<Triangle> triangles;
    std::vector<Point> meshPoints;
    SegmentMap delaunayEdges;

    std::vector<PointData> points;
    UniqueList<int> realPoints;
    std::vector<EdgeData> edges;
    std::unordered_map<Key, int, KeyHasher> edgeMap;

    UniqueList<Point> voronoiPoints;
    SegmentMap voronoiEdges;
    UniqueList<Polygon> voronoiCells;

    Point getCircumcenter(int triangle, int edge, std::vector<Point>& points);
    void callTriangle(std::vector<Point> &point_list);
    PolygonalMesh delaunayToVoronoi();
public:
    TriangleMeshGenerator(std::vector<Point>& point_list, Region region);
    ~TriangleMeshGenerator();
    PolygonalMesh getMesh();
    Triangulation getDelaunayTriangulation();
};

#endif
