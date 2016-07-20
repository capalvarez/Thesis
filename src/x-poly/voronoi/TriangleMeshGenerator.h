#ifndef THESIS_TRIANGLEMESHGENERATOR_H
#define THESIS_TRIANGLEMESHGENERATOR_H

#include "MeshGenerator.h"
#include <vector>
#include "lib/triangle.h"
#include <x-poly/models/polygon/Triangle.h>
#include <unordered_map>
#include <x-poly/voronoi/structures/EdgeData.h>
#include <x-poly/voronoi/structures/PointData.h>
#include <x-poly/utilities/List.h>
#include <x-poly/models/Region.h>
#include <x-poly/voronoi/structures/mapdata.h>
#include <x-poly/models/Triangulation.h>

class TriangleMeshGenerator : public MeshGenerator{
private:
    Mesh mesh;
    std::vector<PointData> points;
    std::vector<EdgeData> edges;
    std::vector<Triangle> triangles;
    std::vector<Point> meshPoints;

    std::unordered_map<Key, int, KeyHasher> edgeMap;

    List<Point> voronoiPoints;
    List<Segment> voronoiEdges;
    List<Polygon> voronoiCells;

    Point getCircumcenter(int triangle, int edge, std::vector<Point>& points);
    void callTriangle(std::vector<Point>& point_list, Region region);
    Mesh delaunayToVoronoi();
public:
    TriangleMeshGenerator(std::vector<Point>& point_list, Region region);
    Mesh getMesh();
    Triangulation getDelaunayTriangulation();
};


#endif
