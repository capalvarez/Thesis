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

    region.cleanSeedPoints();
    region.generateSeedPoints(PointGenerator(functions::random_double(0,20), functions::random_double(0,5)), 20, 5);
    seeds = region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator (seeds, region);
    rectangleRandom = meshGenerator.getMesh();


    /*Rectangle 4x8*/
    std::vector<Point> rectangle4x8_points = {Point(0, 0), Point(8, 0), Point(8, 4), Point(0, 4)};
    Region rectangle4x8(rectangle4x8_points);
    rectangle4x8.generateSeedPoints(PointGenerator(functions::random_double(0,8), functions::random_double(0,4)), 10, 5);
    seeds = rectangle4x8.getSeedPoints();

    meshGenerator = TriangleMeshGenerator (seeds, rectangle4x8);
    rectangle4x8Random = meshGenerator.getMesh();
    rectangle4x8Random.printInFile("rectangle4x8Random.txt");
    rectangle4x8.cleanSeedPoints();

    rectangle4x8.generateSeedPoints(PointGenerator(functions::constantAlternating(), functions::constant()), 12, 6);
    seeds = rectangle4x8.getSeedPoints();

    meshGenerator = TriangleMeshGenerator (seeds, rectangle4x8);
    rectangle4x8ConstantAlternating = meshGenerator.getMesh();
    rectangle4x8ConstantAlternating.printInFile("rectangle4x8ConstantAlternating.txt");
}

Eigen::VectorXd
NumericalTests::loadBothSides(PolygonalMesh mesh, std::vector<PointSegment> restrained, std::vector<double> values) {
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

    return x;
}

Eigen::VectorXd
NumericalTests::clampedWithLoad(PolygonalMesh mesh, std::vector<PointSegment> restricted, double loadValue) {
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

    return x;
}

Eigen::VectorXd NumericalTests::clampedWithBodyForce(PolygonalMesh mesh, PointSegment clamped) {
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

Eigen::VectorXd NumericalTests::clampedWithParabolicLoad(PolygonalMesh mesh) {
    return Eigen::VectorXd();
}

Eigen::VectorXd NumericalTests::fixedXWithParabolicLoad(PolygonalMesh mesh, std::vector<PointSegment> restricted) {
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
    v.writeDisplacements("rectangle4x8ConstantAlternating_displacements.txt", x);

    return x;
}

Eigen::VectorXd
NumericalTests::clampedDisplacement(PolygonalMesh mesh, std::vector<PointSegment> restricted, double displacement) {
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

    return x;
}

Eigen::VectorXd NumericalTests::clampedBothSideLoadMiddle(PolygonalMesh mesh) {
    return Eigen::VectorXd();
}

Eigen::VectorXd NumericalTests::displacementBothSides(PolygonalMesh mesh, std::vector<PointSegment> restricted,
                                                      std::vector<double> displacements) {
    Veamer v;
    BodyForce* f = new None();

    EssentialConstraints essential;
    Constraint const1 (restricted[0], mesh.getPoints().getList(), Constraint::Direction::Total,
                       new Constant(displacements[0]));
    essential.addConstraint(const1, mesh.getPoints().getList());

    Constraint const2 (restricted[1], mesh.getPoints().getList(), Constraint::Direction::Horizontal,
                       new Constant(displacements[1]));
    essential.addConstraint(const2, mesh.getPoints().getList());

    ConstraintsContainer container;
    container.addConstraints(essential, mesh);

    ProblemConditions conditions(container, f, Material(Materials::material::Steel));

    v.initProblem(mesh, conditions);

    Eigen::VectorXd x = v.simulate(mesh);

    return x;
}

void NumericalTests::runTests() {
    std::cout << fixedXWithParabolicLoad(rectangle4x8ConstantAlternating, {PointSegment(Point(0,0), Point(0,4)),
                                                                           PointSegment(Point(8,0), Point(8,4))}) << std::endl;
}














