#include <veamy/models/constraints/values/Function.h>
#include "NumericalTests.h"

class Gravity : public BodyForce{
private:
    double apply(double x, double y){
        return 9.81;
    }
};

double tangencial(double x, double y){
    double P = -1000;
    double D =  4;
    double I = std::pow(D,3)/12;

    return P/(2*I)*(std::pow(D,2)/4-std::pow(y,2));
}

double uX(double x, double y){
    double P = -1000;
    double Ebar = 1e7/(1 - std::pow(0.3,2));
    double vBar = 0.3/(1 - 0.3);
    double D = 4;
    double L = 8;
    double I = std::pow(D,3)/12;


    return -P*y/(6*Ebar*I)*((6*L - 3*x)*x + (2+vBar)*std::pow(y,2) - 3*std::pow(D,2)/2*(1+vBar));
}

double uY(double x, double y){
    double P = -1000;
    double Ebar = 1e7/(1 - std::pow(0.3,2));
    double vBar = 0.3/(1 - 0.3);
    double D = 4;
    double L = 8;
    double I = std::pow(D,3)/12;

    return P/(6*Ebar*I)*(3*vBar*std::pow(y,2)*(L-x) + (3*L-x)*std::pow(x,2));
}

NumericalTests::NumericalTests() {
    /*Rectangle*/
    std::vector<Point> rectangle_points = {Point(0, 0), Point(4, 0), Point(4, 1), Point(0, 1)};
    Region region(rectangle_points);
    region.printInFile("square.txt");

    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 20, 5);
    std::vector<Point> seeds = region.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, region);
    rectangleUniform = meshGenerator.getMesh();
    rectangleUniform.printInFile("ResultadosNumericos\\rectangleUniform.txt");

    region.cleanSeedPoints();
    region.generateSeedPoints(PointGenerator(functions::random_double(0,4), functions::random_double(0,1)), 20, 5);
    seeds = region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator (seeds, region);
    rectangleRandom = meshGenerator.getMesh();
    rectangleRandom.printInFile("ResultadosNumericos\\rectangleRandom.txt");

    /*Rectangle 4x8*/
    std::vector<Point> rectangle4x8_points = {Point(0, -2), Point(8, -2), Point(8, 2), Point(0, 2)};
    Region rectangle4x8(rectangle4x8_points);
    rectangle4x8.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), 12, 6);
    seeds = rectangle4x8.getSeedPoints();

    meshGenerator = TriangleMeshGenerator (seeds, rectangle4x8);
    rectangle4x8ConstantAlternating = meshGenerator.getMesh();
    rectangle4x8ConstantAlternating.printInFile("ResultadosNumericos\\rectangle4x8ConstantAlternating.txt");

    /*L-shape*/
    std::vector<Point> l_points = {Point(10,0), Point(20,0), Point(20,20), Point(0,20), Point(0,10), Point(10,10)};
    Region l_region(l_points);
    l_region.printInFile("l_shape.txt");

    l_region.generateSeedPoints(PointGenerator(functions::random_double(0,20), functions::random_double(0,20)), 10, 10);
    seeds = l_region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, l_region);
    LRandom = meshGenerator.getMesh();
    LRandom.printInFile("ResultadosNumericos\\LRandom.txt");

    l_region.cleanSeedPoints();
    l_region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10,10);
    seeds = l_region.getSeedPoints();
    meshGenerator = TriangleMeshGenerator(seeds, l_region);
    LUniform = meshGenerator.getMesh();
    LUniform.printInFile("ResultadosNumericos\\LUniform.txt");

    /*Romboide*/
    std::vector<Point> romboid_points = {Point(0,0), Point(10,0), Point(15,10), Point(5,10)};
    Region romboid_region(romboid_points);
    romboid_region.generateSeedPoints(PointGenerator(functions::random_double(0,15), functions::random_double(0,15)), 10, 10);
    seeds = romboid_region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, romboid_region);
    romboidRandom = meshGenerator.getMesh();
    romboidRandom.printInFile("ResultadosNumericos\\romboidRandom.txt");

    /*Rectangle with hole*/
    Hole circular = CircularHole(Point(2,1), 0.5);
    region.addHole(circular);
    region.printInFile("squareHole.txt");
    region.generateSeedPoints(PointGenerator(functions::random_double(0,4), functions::random_double(0,1)), 20, 5);
    seeds = region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, region);
    rectangleHoleRandom = meshGenerator.getMesh();
    rectangleHoleRandom.printInFile("ResultadosNumericos\\rectangleHoleRandom.txt");
    region.cleanSeedPoints();
    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 20, 5);
    seeds = region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, region);
    rectangleHoleUniform = meshGenerator.getMesh();
    rectangleHoleUniform.printInFile("ResultadosNumericos\\rectangleHoleUniform.txt");

}

Eigen::VectorXd
NumericalTests::loadBothSides(PolygonalMesh mesh, std::vector<PointSegment> restrained, std::vector<double> values,
                              std::string testName) {
    Veamer v;
    
    NaturalConstraints c;
    SegmentConstraint const1 (restrained[0], mesh.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(-values[0]));
    SegmentConstraint const2 (restrained[1], mesh.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(values[1]));

    c.addConstraint(const1, mesh.getPoints().getList());
    c.addConstraint(const2, mesh.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(c, mesh);

    ProblemConditions conditions(container, Material(Materials::material::Steel));

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
    SegmentConstraint const1 (restricted[0], mesh.getPoints().getList(), Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(const1, mesh.getPoints().getList());

    NaturalConstraints natural;
    SegmentConstraint const2 (restricted[1], mesh.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(loadValue));
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
    SegmentConstraint const1 (clamped, mesh.getPoints().getList(), Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(const1, mesh.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);

    ProblemConditions conditions(container, f, Material(Materials::material::Steel));

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);
    std::string fileName = testName + "ClampedWithBodyForce_displacements.txt";
    v.writeDisplacements(fileName, x);

    return x;
}

Eigen::VectorXd
NumericalTests::clampedDisplacement(PolygonalMesh mesh, std::vector<PointSegment> restricted, double displacement,
                                    std::string testName) {
    Veamer v;
    
    EssentialConstraints essential;
    SegmentConstraint const1 (restricted[0], mesh.getPoints().getList(), Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(const1, mesh.getPoints().getList());

    SegmentConstraint const2 (restricted[1], mesh.getPoints().getList(), Constraint::Direction::Horizontal, new Constant(displacement));
    essential.addConstraint(const2, mesh.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);

    ProblemConditions conditions(container, Material(Materials::material::Steel));

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);

    std::string fileName = testName + "ClampedDisplacement_displacement.txt";
    v.writeDisplacements(fileName, x);

    return x;
}

Eigen::VectorXd NumericalTests::fixedXWithParabolicLoad(PolygonalMesh mesh, std::vector<PointSegment> restricted, std::string testName) {
    Veamer v;
    
    EssentialConstraints essential;
    Function* uXConstraint = new Function(uX);
    Function* uYConstraint = new Function(uY);

    SegmentConstraint const1 (restricted[0], mesh.getPoints().getList(), Constraint::Direction::Horizontal, uXConstraint);
    essential.addConstraint(const1, mesh.getPoints().getList());

    SegmentConstraint const2 (restricted[0], mesh.getPoints().getList(), Constraint::Direction::Vertical, uYConstraint);
    essential.addConstraint(const2, mesh.getPoints().getList());

    NaturalConstraints natural;

    Function* tangencialLoad = new Function(tangencial);

    SegmentConstraint const3 (restricted[1], mesh.getPoints().getList(), Constraint::Direction::Vertical, tangencialLoad);
    natural.addConstraint(const3, mesh.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);
    container.addConstraints(natural, mesh);

    Material m(1e7, 0.3);
    ProblemConditions conditions(container, m);

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);
    std::string fileName = testName + "FixedXWithParabolicLoad_displacement.txt";
    v.writeDisplacements(fileName, x);

    return x;
}

Eigen::VectorXd NumericalTests::clampedBothSideLoadMiddle(PolygonalMesh mesh, std::vector<PointSegment> restricted, PointSegment charged,
                                                          double load, std::string testName) {
    Veamer v;
    
    EssentialConstraints essential;
    SegmentConstraint const1 (restricted[0], mesh.getPoints().getList(), Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(const1, mesh.getPoints().getList());

    SegmentConstraint const2 (restricted[1], mesh.getPoints().getList(), Constraint::Direction::Total, new Constant(0));
    essential.addConstraint(const2, mesh.getPoints().getList());

    NaturalConstraints natural;
    SegmentConstraint const3 (charged, mesh.getPoints().getList(), Constraint::Direction::Vertical, new Constant(load));
    natural.addConstraint(const3, mesh.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);
    container.addConstraints(natural, mesh);

    ProblemConditions conditions(container, Material(Materials::material::Steel));

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);
    std::string fileName = testName + "ClampedBothSideLoadMiddle_displacements.txt";
    v.writeDisplacements(fileName, x);

    return x;
}

void NumericalTests::runTests() {
    double load = 1000;
    double displacement = 1;



    fixedXWithParabolicLoad(rectangle4x8ConstantAlternating, {PointSegment(Point(0,-2), Point(0,2)),
                                                              PointSegment(Point(8,-2), Point(8,2))}, "rectangle4x8");

    /*loadBothSides(rectangleUniform, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                  {load,load}, "rectangleUniform");
    loadBothSides(rectangleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                  {load,load}, "rectangleRandom");
    loadBothSides(rectangleHoleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                  {load,load}, "rectangleHoleRandom");
    loadBothSides(rectangleHoleUniform, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                  {load,load}, "rectangleHoleUniform");
    loadBothSides(rectangle4x8ConstantAlternating, {PointSegment(Point(0,0), Point(0,4)), PointSegment(Point(8,0), Point(8,4))},
                  {load,load} ,"rectangle4x8ConstantAlternating");
    loadBothSides(romboidRandom, {PointSegment(Point(0,0), Point(5,10)), PointSegment(Point(10,0), Point(15,10))},
                  {load,load} ,"romboidRandom");
    loadBothSides(LRandom, {PointSegment(Point(0,10), Point(0,20)), PointSegment(Point(20,0), Point(20,20))},
                  {load,load} ,"LRandom");
    loadBothSides(LUniform, {PointSegment(Point(0,10), Point(0,20)), PointSegment(Point(20,0), Point(20,20))},
                  {load,load} ,"LUniform");

    clampedWithLoad(rectangleUniform, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                    load,"rectangleUniform");
    clampedWithLoad(rectangleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                    load,"rectangleRandom");
    clampedWithLoad(rectangleHoleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                    load,"rectangleHoleRandom");
    clampedWithLoad(rectangleHoleUniform, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                    load,"rectangleHoleUniform");
    clampedWithLoad(rectangle4x8ConstantAlternating, {PointSegment(Point(0,0), Point(0,4)), PointSegment(Point(8,0), Point(8,4))},
                    load,"rectangle4x8ConstantAlternating");
    clampedWithLoad(romboidRandom, {PointSegment(Point(0,0), Point(5,10)), PointSegment(Point(10,0), Point(15,10))},
                    load,"romboidRandom");*/
    clampedWithLoad(LRandom, {PointSegment(Point(0,10), Point(0,20)), PointSegment(Point(20,0), Point(20,20))},
                    load,"LRandom");
    clampedWithLoad(LUniform, {PointSegment(Point(0,10), Point(0,20)), PointSegment(Point(20,0), Point(20,20))},
                    load,"LUniform");

    /*clampedDisplacement(rectangleUniform, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                        displacement, "rectangleUniform");
    clampedDisplacement(rectangleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                        displacement, "rectangleRandom");
    clampedDisplacement(rectangleHoleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                        displacement, "rectangleHoleRandom");
    clampedDisplacement(rectangleHoleUniform, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                        displacement, "rectangleHoleUniform");
    clampedDisplacement(rectangle4x8ConstantAlternating, {PointSegment(Point(0,0), Point(0,4)), PointSegment(Point(8,0), Point(8,4))},
                        displacement, "rectangle4x8ConstantAlternating");
    clampedDisplacement(romboidRandom, {PointSegment(Point(0,0), Point(5,10)), PointSegment(Point(10,0), Point(15,10))},
                        displacement, "romboidRandom");
    clampedDisplacement(LRandom, {PointSegment(Point(20,0), Point(20,20)), PointSegment(Point(0,10), Point(0,20))},
                        displacement, "LRandom");
    clampedDisplacement(LUniform, {PointSegment(Point(20,0), Point(20,20)), PointSegment(Point(0,10), Point(0,20))},
                        displacement, "LUniform");

    clampedWithBodyForce(rectangleUniform, PointSegment(Point(0,0), Point(0,1)), "rectangleUniform");
    clampedWithBodyForce(rectangleRandom, PointSegment(Point(0,0), Point(0,1)), "rectangleRandom");
    clampedWithBodyForce(rectangleHoleRandom, PointSegment(Point(0,0), Point(0,1)), "rectangleHoleRandom");
    clampedWithBodyForce(rectangleHoleUniform, PointSegment(Point(0,0), Point(0,1)), "rectangleHoleUniform");
    clampedWithBodyForce(rectangle4x8ConstantAlternating, PointSegment(Point(0,0), Point(0,4)), "rectangle4x8ConstantAlternating");
    clampedWithBodyForce(romboidRandom, PointSegment(Point(0,0), Point(5,10)), "romboidRandom");
    clampedWithBodyForce(LRandom, PointSegment(Point(20,0), Point(20,20)), "LRandom");
    clampedWithBodyForce(LUniform, PointSegment(Point(20,0), Point(20,20)), "LUniform");

    fixedXWithParabolicLoad(rectangleUniform, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                            "rectangleUniform");
    fixedXWithParabolicLoad(rectangleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                            "rectangleRandom");
    fixedXWithParabolicLoad(rectangleHoleRandom, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                            "rectangleHoleRandom");
    fixedXWithParabolicLoad(rectangleHoleUniform, {PointSegment(Point(0,0), Point(0,1)), PointSegment(Point(4,0), Point(4,1))},
                            "rectangleHoleUniform");
    fixedXWithParabolicLoad(rectangle4x8ConstantAlternating, {PointSegment(Point(0,0), Point(0,4)), PointSegment(Point(8,0), Point(8,4))},
                            "rectangle4x8ConstantAlternating");
    fixedXWithParabolicLoad(romboidRandom, {PointSegment(Point(0,0), Point(5,10)), PointSegment(Point(10,0), Point(15,10))},
                            "romboidRandom");
    fixedXWithParabolicLoad(LRandom, {PointSegment(Point(20,0), Point(20,20)), PointSegment(Point(0,10), Point(0,20))},
                            "LRandom");
    fixedXWithParabolicLoad(LUniform, {PointSegment(Point(20,0), Point(20,20)), PointSegment(Point(0,10), Point(0,20))},
                            "LUniform");

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
                              PointSegment(Point(0,20), Point(20,20)), load, "LRandom");*/
}














