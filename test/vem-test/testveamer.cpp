#include <gtest/gtest.h>
#include <veamy/models/constraints/Constraint.h>
#include <veamy/models/constraints/values/Constant.h>
#include <veamy/Veamer.h>

TEST(VeamerTest, LoadDataFirstOrderTest){
    Veamer v;
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
    Segment constrained2 (2,5);
    Constraint const1 (constrained, Constraint::Direction::Total, new Constant(0));
    c.addConstraint(const1);
    Constraint const2 (constrained2, Constraint::Direction::Horizontal, new Constant(0.1));
    c.addConstraint(const2);

    ConstraintsContainer container;
    container.addConstraints(c);


    v.loadGeometry(m, container, f);

    Eigen::VectorXd x = v.simulate();

    std::cout << x << std::endl << std::endl;
}

