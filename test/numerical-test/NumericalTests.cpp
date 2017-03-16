#include "NumericalTests.h"

NumericalTests::NumericalTests(int order) {
    this->order = order;
    /*One Square*/
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(2,0), Point(0,1), Point(1,1), Point(2,1)};
    std::vector<int> p1 ={0,1,4,3};
    std::vector<int> p2 ={1,2,5,4};
    std::vector<Point> regionPoints = {points[0], points[2], points[5], points[3]};

    std::vector<Polygon> polygons = {Polygon(p1,points), Polygon(p2,points)};
    SegmentMap segments;
    Region r(regionPoints);

<<<<<<< HEAD
    two_squares = Mesh(points, polygons, segments, r);
=======
    two_squares = PolygonalMesh(points, polygons, segments, Region(std::vector<Point>()));
>>>>>>> fracture_all_neighbours

    /*Hundred Square*/
    std::vector<Point> hundred_square_points = {Point(0, 0), Point(20, 0), Point(20, 5), Point(0, 5)};
    Region region(hundred_square_points);
    PointGenerator generator_uniform (functions::uniform(1), functions::uniform(1));

    region.generateSeedPoints(generator_uniform, 20, 5);
    std::vector<Point> seeds = region.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, region);
    hundred_square = meshGenerator.getMesh();

    /*Random Voronoi on (0,1) square*/
    std::vector<Point> points_square = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    Region region1(points_square);
    PointGenerator generator_random(functions::random_double(0,1), functions::random_double(0,1));

    region1.generateSeedPoints(generator_random, 10, 10);
    seeds = region1.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, region1);
    random_voronoi_square = meshGenerator.getMesh();

<<<<<<< HEAD
    /*Rectangle hole with squares*/
    Hole* circle = new CircularHole(Point(0.5, 0.5), 0.25);
=======
    /*BoundingBox hole with squares*/
    Hole* circle = new CircularHole(Point(0.5,0.5),0.25, 10);
>>>>>>> fracture_all_neighbours
    region1.addHole(circle);

    region1.generateSeedPoints(generator_uniform, 10, 10);
    seeds = region1.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, region1);
    rectangle_hole = meshGenerator.getMesh();

    /*Trapezoid*/
    std::vector<Point> trapezoid_points = {Point(0,0), Point(10,3), Point(10,7), Point(0,10)};
    Region trapezoid_region (trapezoid_points);

    trapezoid_region.generateSeedPoints(generator_uniform, 10, 10);
    seeds = trapezoid_region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, trapezoid_region);
    trapezoid = meshGenerator.getMesh();

    /*L shape*/
    std::vector<Point> l_points = {Point(10,0), Point(20,0), Point(20,20), Point(0,20), Point(0,10), Point(10,10)};
    Region l_region(l_points);

    l_region.generateSeedPoints(generator_uniform, 10, 10);
    seeds = l_region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, l_region);
    L = meshGenerator.getMesh();
}


Eigen::VectorXd NumericalTests::two_squares_rightforceX() {
    Veamer v;
    loadRightForceX(two_squares, v, Segment<int>(0,3), Segment<int>(2,5));

    return v.simulate(<#initializer#>);
}

Eigen::VectorXd NumericalTests::two_squares_rightforceY() {
    Veamer v;
    loadRightForceY(two_squares, v, Segment<int>(0,3), Segment<int>(2,5));

    return v.simulate(<#initializer#>);
}

Eigen::VectorXd NumericalTests::two_squares_noforces() {
    Veamer v;
    loadNoForces(two_squares, v, Segment<int>(0,3), Segment<int>(2,5));

    return v.simulate(<#initializer#>);
}

Eigen::VectorXd NumericalTests::hundredsquare_rightforceX() {
    Veamer v;
    loadRightForceX(hundred_square, v, Segment<int>(0,3), Segment<int>(1,2));

    return v.simulate(<#initializer#>);
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

<<<<<<< HEAD
void NumericalTests::loadRightForceX(Mesh m, Veamer &v, Segment<int> leftSide, Segment<int> rightSide) {
=======
void NumericalTests::loadRightForceX(PolygonalMesh m, Veamer &v, Segment leftSide, Segment rightSide) {
>>>>>>> fracture_all_neighbours
    class None : public BodyForce {
        double apply (double x, double y){
            return 0;
        }
    };

    BodyForce* f = new None();

    EssentialConstraints c;
     Constraint const1 (leftSide, Constraint::Direction::Total, new Constant(0));
    c.addConstraint(const1, std::vector<Point>());

    NaturalConstraints natural;
    Constraint const2 (rightSide, Constraint::Direction::Horizontal, new Constant(10));
    natural.addConstraint(const2, std::vector<Point>());

    ConstraintsContainer container;
    container.addConstraints(c, PolygonalMesh());
    container.addConstraints(natural, nullptr);

    ProblemConditions p (container, f, Material());

    v.initProblem(m, p);
}

<<<<<<< HEAD
void NumericalTests::loadRightForceY(Mesh m, Veamer &v, Segment<int> leftSide, Segment<int> rightSide) {
=======
void NumericalTests::loadRightForceY(PolygonalMesh m, Veamer &v, Segment leftSide, Segment rightSide) {
>>>>>>> fracture_all_neighbours
    class None : public BodyForce {
        double apply (double x, double y){
            return 0;
        }
    };

    BodyForce* f = new None();

    EssentialConstraints c;
    Constraint const1 (leftSide, Constraint::Direction::Total, new Constant(0));
    c.addConstraint(const1, std::vector<Point>());

    NaturalConstraints natural;
    Constraint const2 (rightSide, Constraint::Direction::Vertical, new Constant(10));
    natural.addConstraint(const2, std::vector<Point>());

    ConstraintsContainer container;
    container.addConstraints(c, PolygonalMesh());
    container.addConstraints(natural, nullptr);

    ProblemConditions p (container, f, Material());

    v.initProblem(m, p);
}

<<<<<<< HEAD
void NumericalTests::loadNoForces(Mesh m, Veamer &v, Segment<int> leftSide, Segment<int> rightSide) {
=======
void NumericalTests::loadNoForces(PolygonalMesh m, Veamer &v, Segment leftSide, Segment rightSide) {
>>>>>>> fracture_all_neighbours
    class None : public BodyForce {
        double apply (double x, double y){
            return 0;
        }
    };

    BodyForce* f = new None();

    EssentialConstraints c;
    Constraint const1 (leftSide, Constraint::Direction::Total, new Constant(0));
    c.addConstraint(const1, std::vector<Point>());
    Constraint const2 (rightSide, Constraint::Direction::Total, new Constant(10));
    c.addConstraint(const2, std::vector<Point>());

    ConstraintsContainer container;
    container.addConstraints(c, PolygonalMesh());

    ProblemConditions p (container, f, Material());

    v.initProblem(m, p);
}

<<<<<<< HEAD
void NumericalTests::loadTwoForcesX(Mesh m, Veamer &v, Segment<int> leftSide, Segment<int> rightSide) {
=======
void NumericalTests::loadTwoForcesX(PolygonalMesh m, Veamer &v, Segment leftSide, Segment rightSide) {
>>>>>>> fracture_all_neighbours

}

void NumericalTests::runTests() {
    std::cout << two_squares_noforces() << std::endl << std::endl;
    std::cout << two_squares_rightforceX() << std::endl << std::endl;
    std::cout << two_squares_rightforceY() << std::endl << std::endl;
}














