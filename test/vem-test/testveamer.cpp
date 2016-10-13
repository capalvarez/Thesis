#include <gtest/gtest.h>
#include <veamy/models/constraints/Constraint.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/Veamer.h>
#include <x-poly/models/Region.h>
#include <x-poly/models/generator/functions.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>

TEST(VeamerTest, LoadDataFirstOrderTest){
    Veamer v;
    std::vector<Point> points = {Point(0,0), Point(2,0), Point(2,1), Point(0,1)};
    Region region(points);
    region.generatePoints(PointGenerator(functions::constant(), functions::constant()), 5, 5);

    class Sum : public BodyForce{
    private:
        double apply(double x, double y){
            return 0;
        }
    };

    BodyForce* f = new Sum();

    std::vector<Point> seeds = region.getSeedPoints();
    TriangleMeshGenerator g(seeds, region);
    Mesh m = g.getMesh();
    m.printInFile("Idontgetit.txt");

    EssentialConstraints c;
    Segment<int> constrained(0,3);
    Segment<int> constrained2 (2,5);
    Constraint const1 (constrained, Constraint::Direction::Total, new Constant(0));

    c.addConstraint(const1);
    Constraint const2 (constrained2, Constraint::Direction::Horizontal, new Constant(1));
    c.addConstraint(const2);

    ConstraintsContainer container;
    container.addConstraints(c);

    v.loadGeometry(m, container, f);

    Eigen::VectorXd x = v.simulate();

    std::cout << x << std::endl << std::endl;
}

