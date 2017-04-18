#ifndef THESIS_REMESHADAPTER_H
#define THESIS_REMESHADAPTER_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/Region.h>
#include <x-poly/models/PolygonalMesh.h>
#include <x-poly/models/Triangulation.h>
#include <fracture/geometry/BreakableMesh.h>

class RemeshAdapter {
private:
    Region region;

    Region computeRemeshRegion(std::vector<int> remeshPolygons, std::vector<Point> points, BreakableMesh mesh,
                                   std::vector<int> &involved);
public:
    RemeshAdapter(Region region);
    RemeshAdapter(Polygon poly, BreakableMesh mesh);
    RemeshAdapter(std::vector<int> remeshPolygons, std::vector<Point> points, BreakableMesh mesh);
    RemeshAdapter(std::vector<int> remeshPolygons, std::vector<Point> points, BreakableMesh mesh, std::vector<int>& involved);

    std::vector<Polygon> adaptToMesh(Triangulation triangulation, std::vector<int> changedPolygons, PolygonalMesh &m,
                                         std::unordered_map<int, int> pointMap);
    Triangulation triangulate(std::vector<Point> points);
    std::unordered_map<int, int> includeNewPoints(UniqueList<Point> &meshPoints, Triangulation triangulation);
    std::vector<Polygon> remesh(std::vector<Point> points, std::vector<int> changedPolygons, PolygonalMesh &m);
    Region getRegion();
};


#endif 
