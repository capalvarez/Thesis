#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <models/VEMTriangle.h>

double sum(double x, double y){
    return x+y;
}

double norm(double x, double y){
    return pow(x,2) + pow(y,2);
}

TEST(VEMTriangleTest, IntegrateTest){
    double (*f)(double, double);
    std::vector<Point> points = {Point(0,0),Point(1,0),Point(2,0),Point(1,1),Point(0,1)};

    VEMTriangle t(points[0],points[1],points[4]);
    f = &sum;
    EXPECT_FLOAT_EQ(t.integrate(f),1.0/3);

    f = &norm;
    EXPECT_FLOAT_EQ(t.integrate(f),1/6.0);


}

