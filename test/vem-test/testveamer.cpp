#include <gtest/gtest.h>
#include <Veamer.h>
#include <models/constraints/PointConstraint.h>
#include <models/constraints/values/Constant.h>

double sum (double x, double y){
    return x + y;
}

TEST(VeamerTest, LoadDataFirstOrderTest){
    Veamer v(1);
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(2,0), Point(0,1), Point(1,1), Point(2,1)};
    std::vector<int> p1 ={0,1,4,3};
    std::vector<int> p2 ={1,2,5,4};

    std::vector<Polygon> polygons = {Polygon(p1,points), Polygon(p2,points)};
    std::vector<Segment> segments;

    double (*f)(double, double);
    f = sum;

    Mesh m (points,polygons,segments);
    Constraints c;

    PointConstraint* const1 = new PointConstraint(Point(0,0), Constraint::Direction::Total, new Constant(0));
    PointConstraint* const2 = new PointConstraint(Point(0,1), Constraint::Direction::Total, new Constant(0));

    c.addConstraint(const1);
    c.addConstraint(const2);

    v.loadGeometry(m, c, f);

    Eigen::VectorXd x = v.simulate();

    std::cout << x << std::endl << std::endl;
}

TEST(VeamerTest, LoadDataHigherOrderTest){
    Veamer v(2);
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(2,0), Point(2,1), Point(1,1), Point(0,1)};
    std::vector<int> p1 ={0,1,4,5};
    std::vector<int> p2 ={1,2,3,4};

    std::vector<Polygon> polygons = {Polygon(p1,points), Polygon(p2,points)};
    std::vector<Segment> segments;

    double (*f)(double, double);
    f = sum;

    Mesh m (points,polygons,segments);
    Constraints c;
    v.loadGeometry(m, c, f);

    std::vector<Element> elements = v.getElements();
    //std::cout << elements[0].getK() << std::endl << std::endl << elements[1].getK();

    Eigen::MatrixXd K = v.simulate();
    Eigen::FullPivLU<Eigen::MatrixXd> lu(K);

    std::cout << K << std::endl << std::endl << lu.isInvertible();


}

