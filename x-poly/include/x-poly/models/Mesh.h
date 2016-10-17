#ifndef THESIS_MESH_H
#define THESIS_MESH_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <algorithm>
#include <x-poly/voronoi/structures/EdgeData.h>

class Mesh {
protected:
    std::vector<Point> points;
    std::vector<Polygon> polygons;
    std::vector<EdgeData> edges;

public:
    Mesh(std::vector<Point>& p, std::vector<Polygon>& e, std::vector<EdgeData>& s);
    Mesh();
    ~Mesh();

    std::vector<Point> getPoints();
    std::vector<Polygon> getPolygons();
    void printInFile(std::string fileName);
    bool isInBoundary(Point p);

    int findContainerPolygon(Point p);
};


#endif

