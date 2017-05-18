#include <veamy/models/constraints/values/Function.h>
#include "NumericalTests.h"

class None : public BodyForce{
private:
    double apply(double x, double y){
        return 0;
    }
};

class Gravity : public BodyForce{
private:
    double apply(double x, double y){
        return 9.81;
    }
};

double tangencial(double x, double y){
    return 1000*12/(2*64)*(4-std::pow(y,2));
}

NumericalTests::NumericalTests() {
    /*Rectangle*/
    std::vector<Point> rectangle_points = {Point(0, 0), Point(4, 0), Point(4, 1), Point(0, 1)};
    Region region(rectangle_points);

    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 20, 5);
    std::vector<Point> seeds = region.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, region);
    rectangleUniform = meshGenerator.getMesh();
    rectangleUniform.printInFile("ResultadosNumericos\\rectangleUniform.txt");

    region.cleanSeedPoints();
    region.generateSeedPoints(PointGenerator(functions::random_double(0,20), functions::random_double(0,5)), 20, 5);
    seeds = region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator (seeds, region);
    rectangleRandom = meshGenerator.getMesh();
    rectangleRandom.printInFile("ResultadosNumericos\\rectangleRandom.txt");

    /*Rectangle 4x8*/
    std::vector<Point> rectangle4x8_points = {Point(0, 0), Point(8, 0), Point(8, 4), Point(0, 4)};
    Region rectangle4x8(rectangle4x8_points);
    rectangle4x8.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), 12, 6);
    seeds = rectangle4x8.getSeedPoints();

    meshGenerator = TriangleMeshGenerator (seeds, rectangle4x8);
    rectangle4x8ConstantAlternating = meshGenerator.getMesh();
    rectangle4x8ConstantAlternating.printInFile("ResultadosNumericos\\rectangle4x8ConstantAlternating.txt");

    /*L-shape*/
    std::vector<Point> l_points = {Point(10,0), Point(20,0), Point(20,20), Point(0,20), Point(0,10), Point(10,10)};
    Region l_region(l_points);

    l_region.generateSeedPoints(PointGenerator(functions::random_double(0,20), functions::random_double(0,20)), 10, 10);
    seeds = l_region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, l_region);
    LRandom = meshGenerator.getMesh();
    LRandom.printInFile("ResultadosNumericos\\LRandom.txt");

    /*Romboide*/
    std::vector<Point> romboid_points = {Point(0,0), Point(10,0), Point(15,10), Point(5,10)};
    Region romboid_region(romboid_points);
    romboid_region.generateSeedPoints(PointGenerator(functions::random_double(0,15), functions::random_double(0,15)), 10, 10);
    seeds = romboid_region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, romboid_region);
    romboidRandom = meshGenerator.getMesh();
    romboidRandom.printInFile("ResultadosNumericos\\romboidRandom.txt");

    /*Rectangle with hole*/
    Hole circular = CircularHole(Point(5,5), 2);
    region.addHole(circular);
    region.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 5, 5);
    seeds = region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, region);
    rectangleHoleRandom = meshGenerator.getMesh();
    rectangleHoleRandom.printInFile("ResultadosNumericos\\rectangleHoleRandom.txt");
}

Eigen::VectorXd
NumericalTests::loadBothSides(PolygonalMesh mesh, std::vector<PointSegment> restrained, std::vector<double> values,
                              std::string testName) {
    Veamer v;
    BodyForce* f = new None();

    NaturalConstraints c;
    Constraint const1 (restrained[0], mesh.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(values[0]));
    Constraint const2 (restrained[1], mesh.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(values[1]));

    c.addConstraint(const1, mesh.getPoints().getList());
    c.addConstraint(const2, mesh.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(c, mesh);

    ProblemConditions conditions(container, f, Material(Materials::material::Steel));

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);

    std::string fileName = testName + "LoadBothSides_displacements.txt";
    v.writeDisplacements(fileName, x);
    return x;
}

Eigen::VectorXd
NumericalTests::clampedWithLoad(PolygonalMesh mesh, std::vector<PointSegment> restricted, double loadValue,
                                std::string testName) {
    Veamer v;
    BodyForce* f = new None();

    EssentialConstraints essential;
    Constraint const1 (restricted[0], mesh.getPoints().getList(), Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(const1, mesh.getPoints().getList());

    NaturalConstraints natural;
    Constraint const2 (restricted[1], mesh.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(loadValue));
    natural.addConstraint(const2, mesh.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);
    container.addConstraints(natural, mesh);

    ProblemConditions conditions(container, f, Material(Materials::material::Steel));

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);
    std::string fileName = testName + "ClampedWithLoad_displacements.txt";
    v.writeDisplacements(fileName, x);

    return x;
}

Eigen::VectorXd NumericalTests::clampedWithBodyForce(PolygonalMesh mesh, PointSegment clamped, std::string testName) {
    Veamer v;
    BodyForce* f = new Gravity();

    EssentialConstraints essential;
    Constraint const1 (clamped, mesh.getPoints().getList(), Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(const1, mesh.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);

    ProblemConditions conditions(container, f, Material(Materials::material::Steel));

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);

    return x;
}

Eigen::VectorXd
NumericalTests::clampedDisplacement(PolygonalMesh mesh, std::vector<PointSegment> restricted, double displacement,
                                    std::string testName) {
    Veamer v;
    BodyForce* f = new None();

    EssentialConstraints essential;
    Constraint const1 (restricted[0], mesh.getPoints().getList(), Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(const1, mesh.getPoints().getList());

    Constraint const2 (restricted[1], mesh.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(displacement));
    essential.addConstraint(const2, mesh.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);

    ProblemConditions conditions(container, f, Material(Materials::material::Steel));

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);

    std::string fileName = testName + "ClampedDisplacement_displacement.txt";
    v.writeDisplacements(fileName, x);

    return x;
}

Eigen::VectorXd NumericalTests::fixedXWithParabolicLoad(PolygonalMesh mesh, std::vector<PointSegment> restricted, std::string testName) {
    Veamer v;
    BodyForce* f = new None();

    EssentialConstraints essential;
    Constraint const1 (restricted[0], mesh.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(0));
    essential.addConstraint(const1, mesh.getPoints().getList());

    NaturalConstraints natural;

    Function* tangencialLoad = new Function(tangencial);

    Constraint const2 (restricted[1], mesh.getPoints().getList(), Constraint::Direction::Vertical, tangencialLoad);
    natural.addConstraint(const2, mesh.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);
    container.addConstraints(natural, mesh);

    Material m(1e7, 0.3);
    ProblemConditions conditions(container, f, m);

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);
    std::string fileName = testName + "FixedXWithParabolicLoad_displacement.txt";
    v.writeDisplacements(fileName, x);

    return x;
}

Eigen::VectorXd NumericalTests::clampedBothSideLoadMiddle(PolygonalMesh mesh, std::vector<PointSegment> restricted, PointSegment charged,
                                                          double load, std::string testName) {
    Veamer v;
    BodyForce* f = new None();

    EssentialConstraints essential;
    Constraint const1 (restricted[0], mesh.getPoints().getList(), Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(const1, mesh.getPoints().getList());

    Constraint const2 (restricted[1], mesh.getPoints().getList(), Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(const2, mesh.getPoints().getList());

    NaturalConstraints natural;
    Constraint const3 (charged, mesh.getPoints().getList(), Constraint::Direction::Vertical, new Constant(load));
    natural.addConstraint(const3, mesh.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);
    container.addConstraints(natural, mesh);

    ProblemConditions conditions(container, f, Material(Materials::material::Steel));

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);
    std::string fileName = testName + "ClampedBothSideLoadMiddle_displacements.txt";
    v.writeDisplacements(fileName, x);

    return x;
}

void NumericalTests::runTests() {
    double load = 1000;
    double displacement = 1;

    loadBothSides(rectangleUniform, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                  {load,load}, "rectangleUniform");
    loadBothSides(rectangleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                  {load,load}, "rectangleRandom");
    loadBothSides(rectangleHoleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                  {load,load}, "rectangleHoleRandom");
    loadBothSides(rectangle4x8ConstantAlternating, {PointSegment(Point(0,0), Point(0,4)), PointSegment(Point(8,0), Point(8,4))},
                  {load,load} ,"rectangle4x8ConstantAlternating");
    loadBothSides(romboidRandom, {PointSegment(Point(0,0), Point(5,10)), PointSegment(Point(10,0), Point(15,10))},
                  {load,load} ,"romboidRandom");
    loadBothSides(LRandom, {PointSegment(Point(0,10), Point(0,20)), PointSegment(Point(20,0), Point(20,20))},
                  {load,load} ,"LRandom");

    clampedWithLoad(rectangleUniform, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                    load,"rectangleUniform");
    clampedWithLoad(rectangleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                    load,"rectangleRandom");
    clampedWithLoad(rectangleHoleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                    load,"rectangleHoleRandom");
    clampedWithLoad(rectangle4x8ConstantAlternating, {PointSegment(Point(0,0), Point(0,4)), PointSegment(Point(8,0), Point(8,4))},
                    load,"rectangle4x8ConstantAlternating");
    clampedWithLoad(romboidRandom, {PointSegment(Point(0,0), Point(5,10)), PointSegment(Point(10,0), Point(15,10))},
                    load,"romboidRandom");
    clampedWithLoad(LRandom, {PointSegment(Point(20,0), Point(20,20)), PointSegment(Point(0,10), Point(0,20))},
                    load,"LRandom");

    clampedDisplacement(rectangleUniform, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                        displacement, "rectangleUniform");
    clampedDisplacement(rectangleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                        displacement, "rectangleRandom");
    clampedDisplacement(rectangleHoleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                        displacement, "rectangleHoleRandom");
    clampedDisplacement(rectangle4x8ConstantAlternating, {PointSegment(Point(0,0), Point(0,4)), PointSegment(Point(8,0), Point(8,4))},
                        displacement, "rectangle4x8ConstantAlternating");
    clampedDisplacement(romboidRandom, {PointSegment(Point(0,0), Point(5,10)), PointSegment(Point(10,0), Point(15,10))},
                        displacement, "romboidRandom");
    clampedDisplacement(LRandom, {PointSegment(Point(20,0), Point(20,20)), PointSegment(Point(0,10), Point(0,20))},
                        displacement, "LRandom");

    clampedWithBodyForce(rectangleUniform, PointSegment(Point(0,0), Point(0,1)), "rectangleUniform");
    clampedWithBodyForce(rectangleRandom, PointSegment(Point(0,0), Point(0,1)), "rectangleRandom");
    clampedWithBodyForce(rectangleHoleRandom, PointSegment(Point(0,0), Point(0,1)), "rectangleHoleRandom");
    clampedWithBodyForce(rectangle4x8ConstantAlternating, PointSegment(Point(0,0), Point(0,4)), "rectangle4x8ConstantAlternating");
    clampedWithBodyForce(romboidRandom, PointSegment(Point(0,0), Point(5,10)), "romboidRandom");
    clampedWithBodyForce(LRandom, PointSegment(Point(20,0), Point(20,20)), "LRandom");

    fixedXWithParabolicLoad(rectangleUniform, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                            "rectangleUniform");
    fixedXWithParabolicLoad(rectangleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                            "rectangleRandom");
    fixedXWithParabolicLoad(rectangleHoleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                            "rectangleHoleRandom");
    fixedXWithParabolicLoad(rectangle4x8ConstantAlternating, {PointSegment(Point(0,0), Point(0,4)), PointSegment(Point(8,0), Point(8,4))},
                            "rectangle4x8ConstantAlternating");
    fixedXWithParabolicLoad(romboidRandom, {PointSegment(Point(0,0), Point(5,10)), PointSegment(Point(10,0), Point(15,10))},
                            "romboidRandom");
    fixedXWithParabolicLoad(LRandom, {PointSegment(Point(20,0), Point(20,20)), PointSegment(Point(0,10), Point(0,20))},
                            "LRandom");

    clampedBothSideLoadMiddle(rectangleUniform, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                              PointSegment(Point(0,1), Point(4,1)), load, "rectangleUniform");
    clampedBothSideLoadMiddle(rectangleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                              PointSegment(Point(0,1), Point(4,1)), load, "rectangleRandom");
    clampedBothSideLoadMiddle(rectangleHoleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                              PointSegment(Point(0,1), Point(4,1)), load, "rectangleHoleRandom");
    clampedBothSideLoadMiddle(rectangle4x8ConstantAlternating, {PointSegment(Point(0,0), Point(0,4)), PointSegment(Point(8,0), Point(8,4))},
                              PointSegment(Point(0,4), Point(8,4)), load, "rectangle4x8ConstantAlternating");
    clampedBothSideLoadMiddle(romboidRandom, {PointSegment(Point(0,0), Point(5,10)), PointSegment(Point(10,0), Point(15,10))},
                              PointSegment(Point(5,10), Point(15,10)), load, "romboidRandom");
    clampedBothSideLoadMiddle(LRandom, {PointSegment(Point(20,0), Point(20,20)), PointSegment(Point(0,10), Point(0,20))},
                              PointSegment(Point(0,20), Point(20,20)), load, "LRandom");
}














