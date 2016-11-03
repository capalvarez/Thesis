#include "NumericalTests.h"

NumericalTests::NumericalTests(int order) {
    this->order = order;
    /*One Square*/
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(2,0), Point(0,1), Point(1,1), Point(2,1)};
    std::vector<int> p1 ={0,1,4,3};
    std::vector<int> p2 ={1,2,5,4};

    std::vector<Polygon> polygons = {Polygon(p1,points), Polygon(p2,points)};
    std::vector<Segment> segments;

    two_squares = Mesh(points, polygons, segments, Region(std::vector<Point>()));

    /*Hundred Square*/
    std::vector<Point> hundred_square_points = {Point(0, 0), Point(20, 0), Point(20, 5), Point(0, 5)};
    Region region(hundred_square_points);
    PointGenerator generator_uniform (functions::uniform(1), functions::uniform(1));

    region.generatePoints(generator_uniform, 20, 5);
    std::vector<Point> seeds = region.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, region);
    hundred_square = meshGenerator.getMesh();

    /*Random Voronoi on (0,1) square*/
    std::vector<Point> points_square = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    Region region1(points_square);
    PointGenerator generator_random(functions::random_double(0,1), functions::random_double(0,1));

    region1.generatePoints(generator_random, 10, 10);
    seeds = region1.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, region1);
    random_voronoi_square = meshGenerator.getMesh();

    /*Rectangle hole with squares*/
    Hole* circle = new CircularHole(Point(0.5,0.5),0.25, 10);
    region1.addHole(circle);

    region1.generatePoints(generator_uniform, 10, 10);
    seeds = region1.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, region1);
    rectangle_hole = meshGenerator.getMesh();

    /*Trapezoid*/
    std::vector<Point> trapezoid_points = {Point(0,0), Point(10,3), Point(10,7), Point(0,10)};
    Region trapezoid_region (trapezoid_points);

    trapezoid_region.generatePoints(generator_uniform, 10, 10);
    seeds = trapezoid_region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, trapezoid_region);
    trapezoid = meshGenerator.getMesh();

    /*L shape*/
    std::vector<Point> l_points = {Point(10,0), Point(20,0), Point(20,20), Point(0,20), Point(0,10), Point(10,10)};
    Region l_region(l_points);

    l_region.generatePoints(generator_uniform, 10, 10);
    seeds = l_region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, l_region);
    L = meshGenerator.getMesh();
}


Eigen::VectorXd NumericalTests::two_squares_rightforceX() {
    Veamer v(order);
    loadRightForceX(two_squares, v, Segment(0,3), Segment(2,5));

    return v.simulate();
}

Eigen::VectorXd NumericalTests::two_squares_rightforceY() {
    Veamer v(order);
    loadRightForceY(two_squares, v, Segment(0,3), Segment(2,5));

    return v.simulate();
}

Eigen::VectorXd NumericalTests::two_squares_noforces() {
    Veamer v(order);
    loadNoForces(two_squares, v, Segment(0,3), Segment(2,5));

    return v.simulate();
}

Eigen::VectorXd NumericalTests::hundredsquare_rightforceX() {
    Veamer v(order);
    loadRightForceX(hundred_square, v, Segment(0,3), Segment(1,2));

    return v.simulate();
}

Eigen::VectorXd NumericalTests::hundredsquare_rightforceY() {
    return Eigen::Matrix<double, -1, 1, 0, -1, 1>();
}

Eigen::VectorXd NumericalTests::hundredsquare_noforces() {
    return Eigen::Matrix<double, -1, 1, 0, -1, 1>();
}

Eigen::VectorXd NumericalTests::hundredsquare_twoforcesX() {
    return Eigen::Matrix<double, -1, 1, 0, -1, 1>();
}

Eigen::VectorXd NumericalTests::voronoi_rightforceX() {
    return Eigen::Matrix<double, -1, 1, 0, -1, 1>();
}

Eigen::VectorXd NumericalTests::voronoi_rightforceY() {
    return Eigen::Matrix<double, -1, 1, 0, -1, 1>();
}

Eigen::VectorXd NumericalTests::hole_rightforceX() {
    return Eigen::Matrix<double, -1, 1, 0, -1, 1>();
}

Eigen::VectorXd NumericalTests::hole_twoforceX() {
    return Eigen::Matrix<double, -1, 1, 0, -1, 1>();
}

void NumericalTests::loadRightForceX(Mesh m, Veamer &v, Segment leftSide, Segment rightSide) {
    class None : public BodyForce {
        double apply (double x, double y){
            return 0;
        }
    };

    BodyForce* f = new None();

    EssentialConstraints c;
     Constraint const1 (leftSide, Constraint::Direction::Total, new Constant(0));
    c.addConstraint(const1);

    NaturalConstraints natural;
    Constraint const2 (rightSide, Constraint::Direction::Horizontal, new Constant(10));
    natural.addConstraint(const2);

    ConstraintsContainer container;
    container.addConstraints(c);
    container.addConstraints(natural);

    v.initProblem(m, container, f);
}

void NumericalTests::loadRightForceY(Mesh m, Veamer &v, Segment leftSide, Segment rightSide) {
    class None : public BodyForce {
        double apply (double x, double y){
            return 0;
        }
    };

    BodyForce* f = new None();

    EssentialConstraints c;
    Constraint const1 (leftSide, Constraint::Direction::Total, new Constant(0));
    c.addConstraint(const1);

    NaturalConstraints natural;
    Constraint const2 (rightSide, Constraint::Direction::Vertical, new Constant(10));
    natural.addConstraint(const2);

    ConstraintsContainer container;
    container.addConstraints(c);
    container.addConstraints(natural);

    v.initProblem(m, container, f);
}

void NumericalTests::loadNoForces(Mesh m, Veamer &v, Segment leftSide, Segment rightSide) {
    class None : public BodyForce {
        double apply (double x, double y){
            return 0;
        }
    };

    BodyForce* f = new None();

    EssentialConstraints c;
    Constraint const1 (leftSide, Constraint::Direction::Total, new Constant(0));
    c.addConstraint(const1);
    Constraint const2 (rightSide, Constraint::Direction::Total, new Constant(10));
    c.addConstraint(const2);

    ConstraintsContainer container;
    container.addConstraints(c);

    v.initProblem(m, container, f);
}

void NumericalTests::loadTwoForcesX(Mesh m, Veamer &v, Segment leftSide, Segment rightSide) {

}

void NumericalTests::runTests() {
    std::cout << two_squares_noforces() << std::endl << std::endl;
    std::cout << two_squares_rightforceX() << std::endl << std::endl;
    std::cout << two_squares_rightforceY() << std::endl << std::endl;
}














