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
public:
    RemeshAdapter(Polygon poly, int index);
    RemeshAdapter(std::vector<int> remeshPolygons, std::vector<Point> points, BreakableMesh &mesh);
    RemeshAdapter(std::vector<int> remeshPolygons, std::vector<Point> points, BreakableMesh &mesh,
                  std::vector<int> &involved);

    std::vector<Polygon> adaptToMesh(Triangulation triangulation, BreakableMesh &m, std::unordered_map<int, int> pointMap,
                                         std::vector<int> &tipTriangles);
    Triangulation triangulate(std::vector<Point> points, std::vector<Point> meshPoints);
    Triangulation triangulate(std::vector<Point> points, std::vector<Point> meshPoints, std::vector<PointSegment> restrictedSegments);
    std::unordered_map<int, int> includeNewPoints(UniqueList<Point> &meshPoints, Triangulation triangulation);
    std::vector<Polygon> remesh(std::vector<Point> points, BreakableMesh &m);
    Polygon getRegion();
    int getRegionIndex();
};


#endif 
