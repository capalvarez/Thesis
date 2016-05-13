#ifndef THESIS_TRIANGLEDELAUNAYGENERATOR_H
#define THESIS_TRIANGLEDELAUNAYGENERATOR_H

#include "DelaunayGenerator.h"
#include "../geometry/Mesh.h"
#include "../geometry/Point.h"
#include "../geometry/Region.h"
#include <fstream>
#include <vector>


class TriangleDelaunayGenerator : public DelaunayGenerator{
private:
    Mesh delaunay;
public:
    TriangleDelaunayGenerator(std::vector<Point> point_list, Region region);
    ~TriangleDelaunayGenerator();
    Mesh getDelaunayTriangulation();
};


#endif
