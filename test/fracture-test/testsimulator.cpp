#include <gtest/gtest.h>
#include <fracture/FractureSimulator.h>
#include <x-poly/models/generator/functions.h>
#include <veamy/models/constraints/values/Constant.h>

TEST(FractureSimulatorTest, InitTest){
    std::vector<Point> squarePoints = {Point(0,0),Point(3,0),Point(3,3),Point(0,3)};
    Region square (squarePoints);

    PointGenerator generator (functions::uniform(1), functions::uniform(1));

    square.generateSeedPoints(generator, 8, 8);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, square);
    PolygonalMesh mesh = meshGenerator.getMesh();

    Crack crack(Point(0.3,1.5), Point(2.75,1.5), 0.1, 0.3);

    class Sum : public BodyForce{
    private:
        double apply(double x, double y){
            return 0;
        }
    };

    BodyForce* f = new Sum();
    ConstraintsContainer container;
    Material m;

    ProblemConditions conditions(container, f, m);
    FractureSimulator simulator("test", mesh, crack, conditions);
}

TEST(FractureSimulatorTest, SimulateTest){
    std::vector<Point> squarePoints = {Point(0,0),Point(3,0),Point(3,3),Point(0,3)};
    Region square (squarePoints);

    PointGenerator generator (functions::random_double(0,3), functions::random_double(0,3));

    square.generateSeedPoints(generator, 8, 8);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, square);
    PolygonalMesh mesh = meshGenerator.getMesh();
    mesh.printInFile("previous.txt");

    //Crack crack(Point(0.0, 3.0), Point(1.5, 1.5));
    //Crack crack(Point(0.5, 2.0), Point(2.0, 2.3));
    //Crack crack(Point(1.2, 1.8), Point(1.6, 1.8));
    //Crack crack(Point(0.3,3.0), Point(0.7,2.8));
    Crack crack(Point(1.6,0), Point(1.6,0.75));

    class Sum : public BodyForce{
    private:
        double apply(double x, double y){
            return 0;
        }
    };

    BodyForce* f = new Sum();
    EssentialConstraints essential;
    PointSegment constrained(Point(0,0),Point(0,3));
    Constraint const1 (constrained, mesh.getPoints().getList(), Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(const1,  mesh.getPoints().getList());

    NaturalConstraints natural;
    PointSegment constrained2 (Point(3,0),Point(3,3));
    Constraint const2 (constrained2, mesh.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(100));
    natural.addConstraint(const2,  mesh.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);
    container.addConstraints(natural, mesh);

    ProblemConditions conditions(container, f, Material(Materials::material::Steel));

    FractureSimulator simulator("squareUniform", mesh, crack, conditions);
    simulator.simulate(0.1);
}