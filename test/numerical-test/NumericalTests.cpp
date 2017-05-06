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
    rectangleRandom.printInFile("rectangleRandom.txt");
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
    std::cout << clampedWithLoad(rectangleUniform, std::vector<PointSegment>(), 0) << std::endl;
}














