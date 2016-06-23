#ifndef THESIS_MESH_H
#define THESIS_MESH_H

#include <models/polygon/Polygon.h>
#include "models/basic/Point.h"
#include "models/basic/Segment.h"

class Mesh {
private:
    std::vector<Point> points;
    std::vector<Polygon*> elements;
public:
    Mesh();
    ~Mesh();
};


#endif

