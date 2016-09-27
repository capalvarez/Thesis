#ifndef THESIS_TESTS_H
#define THESIS_TESTS_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <veamy/models/constraints/structures/mapdata.h>
#include <x-poly/voronoi/structures/mapdata.h>
#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/polygon/Triangle.h>
#include <x-poly/models/Mesh.h>
#include <models/constraints/Constraints.h>
#include <models/constraints/values/Constant.h>
#include <Veamer.h>
#include <x-poly/models/Region.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <x-poly/models/generator/functions.h>
#include <x-poly/models/hole/CircularHole.h>

#include "body_forces.cpp"

class Tests{
private:
    Mesh one_square;
    Mesh hundred_square;
    Mesh random_voronoi_square;
    Mesh rectangle_hole;
    Mesh trapezoid;
    Mesh L;

public:
    Tests();



};


#endif
