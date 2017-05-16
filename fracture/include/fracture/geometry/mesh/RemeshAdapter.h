#ifndef THESIS_REMESHADAPTER_H
#define THESIS_REMESHADAPTER_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/Region.h>
#include <x-poly/models/PolygonalMesh.h>
#include <x-poly/models/Triangulation.h>
#include <fracture/geometry/BreakableMesh.h>

class RemeshAdapter {
private:
    Polygon region;
    int regionIndex;

    Polygon computeRemeshRegion(std::vector<int> remeshPolygons, std::vector<Point> points, BreakableMesh &mesh,
                               std::vector<int> &involved);
    int getEquivalentIndex(std::unordered_map<int, int> map, int index);
public:
    RemeshAdapter(Polygon poly, int index);
    RemeshAdapter(std::vector<int> remeshPolygons, std::vector<Point> points, BreakableMesh &mesh);
    RemeshAdapter(std::vector<int> remeshPolygons, std::vector<Point> points, BreakableMesh &mesh,
                  std::vector<int> &involved);

    void adaptToMesh(Triangulation triangulation, BreakableMesh &m, std::unordered_map<int, int> pointMap,
                         std::vector<int> &tipTriangles, std::vector<Polygon> &newPolygons);
    void adaptToMesh(Triangulation triangulation, BreakableMesh &m, std::unordered_map<int, int> pointMap,
                         std::vector<Polygon> &newPolygons);
    Triangulation triangulate(std::vector<Point> points, std::vector<Point> meshPoints);
    Triangulation triangulate(Region region, std::vector<Point> points);

    std::unordered_map<int, int> includeNewPoints(UniqueList<Point> &meshPoints, Triangulation triangulation);
    std::unordered_map<int, int> includeNewPoints(UniqueList<Point> &meshPoints, std::vector<Point> points);
    std::vector<Polygon> remesh(std::vector<Point> points, BreakableMesh &m);
    Polygon getRegion();
    int getRegionIndex();
};


#endif 
