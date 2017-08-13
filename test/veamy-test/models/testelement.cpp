#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <x-poly/models/polygon/Polygon.h>
#include <veamy/physics/BodyForce.h>
#include <x-poly/models/PolygonalMesh.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/models/Element.h>

TEST(ElementTest, KMatrixTest){
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(0,1), Point(1,1)};
    Region region(points);

    std::vector<int> p1 ={0,1,3,2};

    std::vector<Polygon> polygons = {Polygon(p1,points)};
    SegmentMap segments;

    PolygonalMesh m(points, polygons, segments, region);

    ConstraintsContainer container;
    DOFS dofs;
    UniqueList<Point> p;
    p.push_list(points);

    ProblemConditions conditions(container, Material(1, 0.3));

    Element e (conditions, polygons[0], p, dofs);

}

