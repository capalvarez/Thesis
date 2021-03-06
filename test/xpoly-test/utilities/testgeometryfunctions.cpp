#include <x-poly/models/basic/Point.h>
#include <x-poly/utilities/geometryFunctions.h>
#include <gtest/gtest.h>

TEST(GeometryFunctionsTest, CollinearTest){
    Point p1(0,0);
    Point p2(1,1);

    Point pTestBetween(0.25,0.25);
    Point pTestOutside(2,2);
    Point pTestNotCollinear(3.5,3.4);
    Point pTestNot2 (0.2,0.25);
    Point borderCase(0.25,0.24999999999999999);

    EXPECT_TRUE(geometry_functions::collinear(p1,p2,p1));
    EXPECT_TRUE(geometry_functions::collinear(p1,p2,p2));
    EXPECT_TRUE(geometry_functions::collinear(p1,p2,pTestBetween));
    EXPECT_TRUE(geometry_functions::collinear(p1,p2,pTestOutside));
    EXPECT_FALSE(geometry_functions::collinear(p1,p2,pTestNotCollinear));
    EXPECT_FALSE(geometry_functions::collinear(p1,p2,pTestNot2));
    EXPECT_TRUE(geometry_functions::collinear(p1,p2,borderCase));
}

TEST(GeometryFunctionsTest, TriangleAreaTest){
    Point p1(1,0);
    Point p2(0,1);
    Point p3(4,3);
    Point p4(2,5);

    ASSERT_EQ(geometry_functions::triangleArea(p1,p2,Point(0,0)), 0.5);
    ASSERT_EQ(geometry_functions::triangleArea(p3,p4,Point(0,0)), 7);
}