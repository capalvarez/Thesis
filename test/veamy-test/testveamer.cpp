#include <gtest/gtest.h>
#include <veamy/models/constraints/Constraint.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/Veamer.h>
#include <x-poly/models/Region.h>
#include <x-poly/models/generator/functions.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <veamy/models/constraints/values/Function.h>

double uXPatch(double x, double y){
    return x;
}

double uYPatch(double x, double y){
    return x + y;
}

TEST(VeamerTest, OnlyEssentialTest){
    Veamer v;
    std::vector<Point> points = {Point(0,0), Point(2,0), Point(2,1), Point(0,1)};
    Region region(points);
    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);

    std::vector<Point> seeds = region.getSeedPoints();
    TriangleMeshGenerator g(seeds, region);
    PolygonalMesh m = g.getMesh();
    m.printInFile("first.txt");

    EssentialConstraints c;
    PointSegment constrained(Point(0,0),Point(0,1));
    PointSegment constrained2 (Point(2,0),Point(2,1));
    SegmentConstraint const1 (constrained, m.getPoints().getList(), Constraint::Direction::Total, new Constant(0));

    c.addConstraint(const1, m.getPoints().getList());
    SegmentConstraint const2 (constrained2, m.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(1));
    c.addConstraint(const2, m.getPoints().getList());

   /* NaturalConstraints n;
    PointSegment const3(Point(0,0),Point(2,0));
    Constraint constraint3(const3,m.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(2));
    n.addConstraint(constraint3, m.getPoints().getList());*/

    ConstraintsContainer container;
    container.addConstraints(c, m);
    // container.addConstraints(n,m);

    ProblemConditions conditions(container, Material(Materials::material::Steel));

    v.initProblem(m, conditions);

    Eigen::VectorXd x = v.simulate(m);
    m.printInFile("second.txt");
}

TEST(VeamerTest, OnlyNaturalTest){
    Veamer v;
    std::vector<Point> points = {Point(0,0), Point(2,0), Point(2,1), Point(0,1)};
    Region region(points);
    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 3, 3);

    std::vector<Point> seeds = region.getSeedPoints();
    TriangleMeshGenerator g(seeds, region);
    PolygonalMesh m = g.getMesh();
    m.printInFile("first.txt");

    EssentialConstraints c;
    PointSegment constrained(Point(0,0),Point(0,1));
    SegmentConstraint const1 (constrained, m.getPoints().getList(), Constraint::Direction::Total, new Constant(0));

    c.addConstraint(const1, m.getPoints().getList());

    NaturalConstraints n;
    PointSegment const3(Point(2,0),Point(2,1));
    SegmentConstraint constraint3(const3,m.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(1000));
    n.addConstraint(constraint3, m.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(c, m);
    container.addConstraints(n,m);

    ProblemConditions conditions(container,  Material(Materials::material::Steel));

    v.initProblem(m, conditions);

    Eigen::VectorXd x = v.simulate(m);
    std::cout << x << std::endl;
    m.printInFile("second.txt");
}

TEST(VeamerTest, OnlyBodyForceTest){
    Veamer v;
    std::vector<Point> points = {Point(0,0), Point(2,0), Point(2,1), Point(0,1)};
    Region region(points);
    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 3, 3);

    std::vector<Point> seeds = region.getSeedPoints();
    TriangleMeshGenerator g(seeds, region);
    PolygonalMesh m = g.getMesh();
    m.printInFile("first.txt");

    EssentialConstraints c;
    PointSegment constrained(Point(0,0),Point(0,1));
    SegmentConstraint const1 (constrained, m.getPoints().getList(), Constraint::Direction::Total, new Constant(0));

    c.addConstraint(const1, m.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(c, m);

    ProblemConditions conditions(container,  Material(Materials::material::Steel));

    v.initProblem(m, conditions);

    Eigen::VectorXd x = v.simulate(m);
    std::cout << x << std::endl;
    m.printInFile("second.txt");
}

TEST(VeamerTest, EquilibriumPatchTest){
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    Region region(points);
    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 5, 5);
    std::vector<Point> seeds = region.getSeedPoints();
    
    TriangleMeshGenerator generator(seeds, region);
    PolygonalMesh mesh = generator.getMesh();
    mesh.printInFile("equilibrium.txt");
}

TEST(VeamerTest, PatchTest){
    std::vector<Point> rectangle4x8_points = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Region rectangle4x8(rectangle4x8_points);
    rectangle4x8.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);

    std::vector<Point> seeds = rectangle4x8.getSeedPoints();
    TriangleMeshGenerator meshGenerator = TriangleMeshGenerator (seeds, rectangle4x8);
    PolygonalMesh mesh = meshGenerator.getMesh();
    mesh.printInFile("rectangle.txt");

    Veamer v;

    EssentialConstraints essential;
    Function* uXConstraint = new Function(uXPatch);
    Function* uYConstraint = new Function(uYPatch);

    PointSegment leftSide(Point(0,-2), Point(0,2));
    SegmentConstraint leftX (leftSide, mesh.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(leftX, mesh.getPoints());
    SegmentConstraint  leftY (leftSide, mesh.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(leftY, mesh.getPoints());

    PointSegment downSide(Point(0,-2), Point(8,-2));
    SegmentConstraint downX (downSide, mesh.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(downX, mesh.getPoints());
    SegmentConstraint  downY (downSide, mesh.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(downY, mesh.getPoints());

    PointSegment rightSide(Point(8,-2), Point(8, 2));
    SegmentConstraint rightX (rightSide, mesh.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(rightX, mesh.getPoints());
    SegmentConstraint  rightY (rightSide, mesh.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(rightY, mesh.getPoints());

    PointSegment topSide(Point(0, 2), Point(8, 2));
    SegmentConstraint topX (topSide, mesh.getPoints(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(topX, mesh.getPoints());
    SegmentConstraint  topY (topSide, mesh.getPoints(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(topY, mesh.getPoints());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);

    Material m(1e7, 0.3);
    ProblemConditions conditions(container, m);

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);
    std::string fileName = "displacement.txt";
    v.writeDisplacements(fileName, x);
}