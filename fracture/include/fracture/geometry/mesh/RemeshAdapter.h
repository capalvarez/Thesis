#ifndef THESIS_REMESHADAPTER_H
#define THESIS_REMESHADAPTER_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/Region.h>
#include <x-poly/models/Mesh.h>

class RemeshAdapter {
private:
    Region region;

    Region computeRemeshRegion(std::vector<Polygon> remeshPolygons, std::vector<Point> points);
public:
    RemeshAdapter(Region region);
    RemeshAdapter(std::vector<Polygon> remeshPolygons, std::vector<Point> points);

    std::vector<Polygon> remesh(std::vector<Point> points, std::vector<int> changedPolygons, Mesh& m);
};


#endif 
