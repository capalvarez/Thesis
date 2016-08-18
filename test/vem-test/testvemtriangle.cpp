#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <models/integration/IntegrationTriangle.h>
#include "testfunctions/testfunctions.h"

TEST(VEMTriangleTest, IntegrateTest){
    double (*f)(double, double);
    std::vector<Point> points = {Point(0,0),Point(1,0),Point(2,0),Point(1,1),Point(0,1)};

    IntegrationTriangle t(0,1,4);
    IntegrationTriangle t2(0,2,3);
    f = testfunctions::sum;
    EXPECT_FLOAT_EQ(t.integrate(f,points),1.0/3);
    EXPECT_FLOAT_EQ(t2.integrate(f,points),8.0/6);

    f = testfunctions::norm;
    EXPECT_FLOAT_EQ(t.integrate(f,points),1/6.0);
    EXPECT_FLOAT_EQ(t2.integrate(f,points),4.0/3);
}

