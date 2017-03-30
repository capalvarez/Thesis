#include <gtest/gtest.h>
#include <veamy/models/constraints/Constraint.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/Veamer.h>
#include <x-poly/models/Region.h>
#include <x-poly/models/generator/functions.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>

TEST(VeamerTest, OnlyEssentialTest){
    Veamer v;
    std::vector<Point> points = {Point(0,0), Point(2,0), Point(2,1), Point(0,1)};
    Region region(points);
    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);

    class Sum : public BodyForce{
    private:
        double apply(double x, double y){
            return 0;
        }
    };

    BodyForce* f = new Sum();

    std::vector<Point> seeds = region.getSeedPoints();
    TriangleMeshGenerator g(seeds, region);
    PolygonalMesh m = g.getMesh();
    m.printInFile("first.txt");

    EssentialConstraints c;
    PointSegment constrained(Point(0,0),Point(0,1));
    PointSegment constrained2 (Point(2,0),Point(2,1));
    Constraint const1 (constrained, m.getPoints().getList(), Constraint::Direction::Total, new Constant(0));

    c.addConstraint(const1, m.getPoints().getList());
    Constraint const2 (constrained2, m.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(1));
    c.addConstraint(const2, m.getPoints().getList());

   /* NaturalConstraints n;
    PointSegment const3(Point(0,0),Point(2,0));
    Constraint constraint3(const3,m.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(2));
    n.addConstraint(constraint3, m.getPoints().getList());*/

    ConstraintsContainer container;
    container.addConstraints(c, m);
    // container.addConstraints(n,m);

    ProblemConditions conditions(container, f, Material(Materials::material::Steel));

    v.initProblem(m, conditions);

    Eigen::VectorXd x = v.simulate(m);
    m.printInFile("second.txt");
}

TEST(VeamerTest, OnlyNaturalTest){
    Veamer v;
    std::vector<Point> points = {Point(0,0), Point(2,0), Point(2,1), Point(0,1)};
    Region region(points);
    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 3, 3);

    class Sum : public BodyForce{
    private:
        double apply(double x, double y){
            return 0;
        }
    };

    BodyForce* f = new Sum();

    std::vector<Point> seeds = region.getSeedPoints();
    TriangleMeshGenerator g(seeds, region);
    PolygonalMesh m = g.getMesh();
    m.printInFile("first.txt");

    EssentialConstraints c;
    PointSegment constrained(Point(0,0),Point(0,1));
    Constraint const1 (constrained, m.getPoints().getList(), Constraint::Direction::Total, new Constant(0));

    c.addConstraint(const1, m.getPoints().getList());

    NaturalConstraints n;
    PointSegment const3(Point(2,0),Point(2,1));
    Constraint constraint3(const3,m.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(1000));
    n.addConstraint(constraint3, m.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(c, m);
    container.addConstraints(n,m);

    ProblemConditions conditions(container, f, Material(Materials::material::Steel));

    v.initProblem(m, conditions);

    Eigen::VectorXd x = v.simulate(m);
    m.printInFile("second.txt");
}