#ifndef THESIS_TRIANGLEMESHGENERATOR_H
#define THESIS_TRIANGLEMESHGENERATOR_H

#include "MeshGenerator.h"
#include "models/Mesh.h"
#include "models/basic/Point.h"
#include "models/Region.h"
#include <vector>
#include "lib/triangle.h"
#include "models/polygon/Triangle.h"
#include <unordered_map>
#include <voronoi/structures/EdgeData.h>
#include <voronoi/structures/PointData.h>
#include <utilities/List.h>
#include "voronoi/structures/mapdata.h"

class TriangleMeshGenerator : public MeshGenerator{
private:
    Mesh mesh;
    std::vector<PointData> points;
    std::vector<EdgeData> edges;
    std::vector<Triangle*> triangles;
    std::vector<Point> meshPoints;

    std::unordered_map<Key, int, KeyHasher> edgeMap;

    List<Point> voronoiPoints;
    List<Segment> voronoiEdges;
    List<Polygon> voronoiCells;

    void callTriangle(std::vector<Point>& point_list, Region region);
    Mesh delaunayToVoronoi();

    Point getCircumcenter(int triangle, int edge, std::vector<Point>& points);
public:
    TriangleMeshGenerator(std::vector<Point>& point_list, Region region);
    Mesh getMesh();
};


#endif
