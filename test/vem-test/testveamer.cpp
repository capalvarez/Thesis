#include <gtest/gtest.h>
#include <Veamer.h>
#include <models/constraints/Constraint.h>
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

    class Sum : public BodyForce{
    private:
        double apply(double x, double y){
            return 0;
        }
    };

    BodyForce* f = new Sum();

    Mesh m (points,polygons,segments);

    EssentialConstraints c;
    Segment constrained(0,3);
    Constraint const1 (constrained, Constraint::Direction::Total, new Constant(0));
    c.addConstraint(const1);

    NaturalConstraints natural;
    Segment contrained2(2,5);
    Constraint const2 (contrained2, Constraint::Direction::Horizontal, new Constant(100));
    natural.addConstraint(const2);

    ConstraintsContainer container;
    container.addConstraints(c);
    container.addConstraints(natural);

    v.loadGeometry(m, container, f);

    Eigen::VectorXd x = v.simulate();

    std::cout << x << std::endl << std::endl;
}

TEST(VeamerTest, LoadDataHigherOrderTest){
    /*Veamer v(2);
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(2,0), Point(2,1), Point(1,1), Point(0,1)};
    std::vector<int> p1 ={0,1,4,5};
    std::vector<int> p2 ={1,2,3,4};

    std::vector<Polygon> polygons = {Polygon(p1,points), Polygon(p2,points)};
    std::vector<Segment> segments;

    double (*f)(double, double);
    f = sum;

    Mesh m (points,polygons,segments);
    EssentialConstraints c;
    v.loadGeometry(m, c, f);

    std::vector<Element> elements = v.getElements();
    //std::cout << elements[0].getK() << std::endl << std::endl << elements[1].getK();

    Eigen::MatrixXd K = v.simulate();
    //Eigen::FullPivLU<Eigen::MatrixXd> lu(K);

    //std::cout << K << std::endl << std::endl << lu.isInvertible();*/


}

