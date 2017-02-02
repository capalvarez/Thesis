#ifndef THESIS_REMESHADAPTER_H
#define THESIS_REMESHADAPTER_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/Region.h>
#include <x-poly/models/Mesh.h>
#include <x-poly/models/Triangulation.h>

class RemeshAdapter {
private:
    Region region;

    Region computeRemeshRegion(std::vector<Polygon> remeshPolygons, std::vector<Point> points);
public:
    RemeshAdapter(Region region);
    RemeshAdapter(std::vector<Polygon> remeshPolygons, std::vector<Point> points);

    std::vector<Polygon> adaptToMesh(Triangulation triangulation, std::vector<int> changedPolygons, Mesh &m,
                                     std::unordered_map<int, int> pointMap);
    Triangulation triangulate(std::vector<Point> points);
    std::unordered_map<int, int> includeNewPoints(UniqueList<Point> &meshPoints, Triangulation triangulation);
    std::vector<Polygon> remesh(std::vector<Point> points, std::vector<int> changedPolygons, Mesh &m);
};


#endif 
