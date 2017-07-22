#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/polygon/Polygon.h>
#include <veamy/quadrature/QuadraturePolygon.h>

TEST(QuadraturePolygonTest, ConstantTest){
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1), Point(0.5,1), Point(1,2), Point(0,2)};
    std::vector<int> square_points = {0,1,2,3};

    Polygon square(square_points, points);
    QuadraturePolygon q(square);

    class Sum : public BodyForce{
    private:
        double apply(double x, double y){
            return 1;
        }
    };

    BodyForce* f = new Sum();

    EXPECT_EQ(q.integrate(f, points), 1);

    std::vector<int> triangle_points = {0,1,4};
    Polygon triangle(triangle_points, points);
    q = QuadraturePolygon(triangle);

    EXPECT_EQ(q.integrate(f, points), 0.5);

    std::vector<int> nonconvex_points = {0,1,5,4,6};
    Polygon nonconvex(nonconvex_points, points);
    q = QuadraturePolygon(nonconvex);

    EXPECT_EQ(q.integrate(f, points), 1.5);
}

TEST(QuadraturePolygonTest, LinearTest){
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1), Point(0.5,1), Point(1,2), Point(0,2)};
    std::vector<int> square_points = {0,1,2,3};

    Polygon square(square_points, points);
    QuadraturePolygon q(square);

    class Sum : public BodyForce{
    private:
        double apply(double x, double y){
            return x+y;
        }
    };

    BodyForce* f = new Sum();

    EXPECT_EQ(q.integrate(f, points), 1);

    std::vector<int> triangle_points = {0,1,4};
    Polygon triangle(triangle_points, points);
    q = QuadraturePolygon(triangle);

    EXPECT_EQ(q.integrate(f, points), 5.0/12);

    std::vector<int> nonconvex_points = {0,1,5,4,6};
    Polygon nonconvex(nonconvex_points, points);
    q = QuadraturePolygon(nonconvex);

    EXPECT_FLOAT_EQ(q.integrate(f, points), 23.0/12);
}

