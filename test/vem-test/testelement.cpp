#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <x-poly/models/polygon/Polygon.h>
#include <veamy/physics/BodyForce.h>
#include <x-poly/models/Mesh.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/models/dof/DOFS.h>
#include <veamy/models/Element.h>

TEST(ElementTest, KMatrixTest){
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(0,1), Point(1,1)};
    std::vector<int> p1 ={0,1,3,2};

    std::vector<Polygon> polygons = {Polygon(p1,points)};
    SegmentMap segments;

    class Sum : public BodyForce{
    private:
        double apply(double x, double y){
            return 0;
        }
    };

    BodyForce* f = new Sum();
    Mesh m (points,polygons,segments);

    ConstraintsContainer container;
    DOFS dofs;
    List<Point> p;
    p.push_list(points);

    ProblemConditions conditions(container, f, Material());

    Element e (conditions, polygons[0], p, dofs);

}

