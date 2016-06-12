#include <gtest/gtest.h>
#include <geometry/Point.h>
#include<utilities/convexHull.h>

TEST(ConvexHullTest, OrientationTest){
    std::vector<Point> points = {Point(2,0),Point(5,5),Point(0,3),Point(0,0),
                                Point(1,2),Point(0.5,1),Point(0,2)};
    EXPECT_EQ(convex::orientation(points[0],points[1],points[2]), 19);
    EXPECT_EQ(convex::orientation(points[3], points[2], points[0]), -6);
    EXPECT_EQ(convex::orientation(points[4],points[5],points[6]), -1);
}

TEST(ConvexHullTest, ConvexHullFunctionTest){

}

TEST(ConvexHullTest, RotatingCalipersTest){

}

