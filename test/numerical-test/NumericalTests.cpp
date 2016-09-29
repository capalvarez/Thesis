#include "NumericalTests.h"

NumericalTests::NumericalTests() {
    /*One Square*/
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(0,1), Point(1,1)};
    std::vector<int> p ={0,1,2,3};

    std::vector<Polygon> polygons = {Polygon(p,points)};
    std::vector<Segment> segments;

    one_square = Mesh(points,polygons,segments);

    /*Hundred Square*/
    std::vector<Point> hundred_square_points = {Point(0, 0), Point(20, 0), Point(20, 5), Point(0, 5)};
    Region region(hundred_square_points);
    PointGenerator generator_uniform (functions::uniform(1), functions::uniform(1));

    region.generatePoints(generator_uniform, 20, 5);
    std::vector<Point> seeds = region.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, region);
    hundred_square = meshGenerator.getMesh();

    /*Random Voronoi on (0,1) square*/
    Region region1(points);
    PointGenerator generator_random(functions::random_double(0,1), functions::random_double(0,1));

    region1.generatePoints(generator_random, 10, 10);
    seeds = region1.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, region1);
    random_voronoi_square = meshGenerator.getMesh();

    /*Rectangle hole with squares*/
    Hole* circle = new CircularHole(Point(0.5,0.5),0.1);
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


Eigen::VectorXd NumericalTests::onesquare_rightforceX() {
    Veamer v(1);

    class None : public BodyForce {
        double apply (double x, double y){
            return 0;
        }
    };

    BodyForce* f = new None();

    EssentialConstraints c;
    Segment constrained(0,3);
    Constraint const1 (constrained, Constraint::Direction::Total, new Constant(0));
    c.addConstraint(const1);

    NaturalConstraints natural;
    Segment contrained2(1,2);
    Constraint const2 (contrained2, Constraint::Direction::Total, new Constant(10));
    natural.addConstraint(const2);

    ConstraintsContainer container;
    container.addConstraints(c);
    container.addConstraints(natural);

    v.loadGeometry(one_square, container, f);

    return v.simulate();

}

Eigen::VectorXd NumericalTests::onesquare_rightforceY() {
    return Eigen::Matrix<double, -1, 1, 0, -1, 1>();
}

Eigen::VectorXd NumericalTests::onesquare_noforces() {
    return Eigen::Matrix<double, -1, 1, 0, -1, 1>();
}

Eigen::VectorXd NumericalTests::hundredsquare_rightforceX() {
    return Eigen::Matrix<double, -1, 1, 0, -1, 1>();
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

Eigen::VectorXd NumericalTests::hundredsquare_distributedforce() {
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

void NumericalTests::runTests() {
    std::cout << onesquare_rightforceX();
}













