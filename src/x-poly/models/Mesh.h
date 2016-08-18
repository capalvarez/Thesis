#ifndef THESIS_MESH_H
#define THESIS_MESH_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <algorithm>

class Mesh {
private:
    std::vector<Point> points;
    std::vector<Polygon*> elements;
public:
    Mesh(std::vector<Point>& p, std::vector<Polygon*>& e);
    Mesh();
    ~Mesh();
};


#endif

