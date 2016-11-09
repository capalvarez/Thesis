#include <gtest/gtest.h>
#include <fracture/FractureSimulator.h>
#include <x-poly/models/generator/functions.h>

TEST(FractureSimulatorTest, InitTest){
    std::vector<Point> squarePoints = {Point(0,0),Point(3,0),Point(3,3),Point(0,3)};
    Region square (squarePoints);

    PointGenerator generator (functions::uniform(1), functions::uniform(1));

    square.generatePoints(generator, 3, 3);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, square);
    Mesh mesh = meshGenerator.getMesh();

    Crack crack(Point(0.25,1.5), Point(2.75,1.5), 0.1, 0.8);

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
    FractureSimulator simulator(mesh, crack, conditions);
}

TEST(FractureSimulatorTest, SimulateTest){
    std::vector<Point> squarePoints = {Point(0,0),Point(3,0),Point(3,3),Point(0,3)};
    Region square (squarePoints);

    PointGenerator generator (functions::uniform(1), functions::uniform(1));

    square.generatePoints(generator, 3, 3);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, square);
    Mesh mesh = meshGenerator.getMesh();

    Crack crack(Point(0.3,1.5), Point(0.7,1.5), 0.1, 2.5);

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
    FractureSimulator simulator(mesh, crack, conditions);

    simulator.simulate(0.1,100);



}