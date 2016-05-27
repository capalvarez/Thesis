#include <geometry/Point.h>
#include <geometry/geometryFunctions.cpp>
#include "gtest/gtest.h"

TEST(GeometryFunctionsTest, CollinearTest){
    Point p1(0,0);
    Point p2(1,1);

    Point pTestBetween(0.25,0.25);
    Point pTestOutside(2,2);
    Point pTestNotCollinear(3.5,3.4);

    EXPECT_TRUE(geometry_functions::collinear(p1,p2,pTestBetween));
    EXPECT_TRUE(geometry_functions::collinear(p1,p2,pTestOutside));
    EXPECT_FALSE(geometry_functions::collinear(p1,p2,pTestNotCollinear));
}