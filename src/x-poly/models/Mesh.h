#ifndef THESIS_MESH_H
#define THESIS_MESH_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <algorithm>

class Mesh {
private:
    std::vector<Point> points;
    std::vector<Polygon> elements;
    std::vector<Segment> edges;
public:
    Mesh(std::vector<Point>& p, std::vector<Polygon>& e, std::vector<Segment>& s);
    Mesh();
    ~Mesh();

    std::vector<Point> getPoints();
    std::vector<Segment> getEdges();
    std::vector<Polygon> getElements();

    void printInFile(std::string fileName);
    void breakPolygons(Segment s);
};


#endif

