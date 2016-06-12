#include <gtest/gtest.h>
#include <geometry/Point.h>
#include <utilities/convexHull.h>

TEST(ConvexHullTest, OrientationTest){
    std::vector<Point> points = {Point(2,0),Point(5,5),Point(0,3),Point(0,0),
                                Point(1,2),Point(0.5,1),Point(0,2)};
    EXPECT_EQ(convex::orientation(points[0],points[1],points[2]), 19);
    EXPECT_EQ(convex::orientation(points[3], points[2], points[0]), -6);
    EXPECT_EQ(convex::orientation(points[4],points[5],points[6]), -1);
}

TEST(ConvexHullTest, ConvexHullFunctionTest){
    std::vector<Point> points = {Point(0,2), Point(3,4), Point(6,2), Point(3,0), Point(2,2), Point(4,1), Point(4,3)};
    std::vector<Point> upper;
    std::vector<Point> lower;

    convex::convexHull(points,upper,lower);

    std::vector<Point> expectedU = {Point(0,2), Point(3,4), Point(6,2)};
    std::vector<Point> expectedL = {Point(0,2), Point(3,0), Point(6,2)};

    EXPECT_EQ(upper,expectedU);
    EXPECT_EQ(lower, expectedL);
}

TEST(ConvexHullTest, RotatingCalipersTest){

}

