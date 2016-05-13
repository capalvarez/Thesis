#ifndef THESIS_MESH_H
#define THESIS_MESH_H

#include "Point.h"
#include "Segment.h"

struct Point_Data{
    Point point = *new Point(0,0);
    int edge;
};

struct Edge_Data{
    Segment edge = *new Segment(-1,-1);
    int polygon1;
    int polygon2;
};

class Mesh {
public:
    Mesh();
    ~Mesh();
};


#endif

