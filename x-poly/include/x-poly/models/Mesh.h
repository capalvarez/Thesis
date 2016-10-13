#ifndef THESIS_MESH_H
#define THESIS_MESH_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <algorithm>

class Mesh {
protected:
    std::vector<Point> points;
    std::vector<Polygon> polygons;
    std::vector<Segment<int>> edges;
    std::vector<Segment<int>> boundary;

public:
    Mesh(std::vector<Point>& p, std::vector<Polygon>& e, std::vector<Segment<int>>& s);
    Mesh();
    ~Mesh();

    std::vector<Point> getPoints();
    std::vector<Segment<int>> getEdges();
    std::vector<Polygon> getPolygons();
    void printInFile(std::string fileName);
    bool isInBoundary(Point p);
};


#endif

