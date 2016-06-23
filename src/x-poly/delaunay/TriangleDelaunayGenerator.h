#ifndef THESIS_TRIANGLEDELAUNAYGENERATOR_H
#define THESIS_TRIANGLEDELAUNAYGENERATOR_H

#include "DelaunayGenerator.h"
#include "models/Mesh.h"
#include "models/basic/Point.h"
#include "models/Region.h"
#include <vector>
#include "lib/triangle.h"
#include "models/polygon/Triangle.h"
#include "delaunay/structures/PointData.h"
#include "delaunay/structures/EdgeData.h"

class TriangleDelaunayGenerator : public DelaunayGenerator{
private:
    Mesh delaunay;
public:
    TriangleDelaunayGenerator(std::vector<Point>& point_list, Region region);
    ~TriangleDelaunayGenerator();
    Mesh getDelaunayTriangulation();
};


#endif
