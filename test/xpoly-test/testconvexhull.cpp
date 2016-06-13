#include "testconvexhull.h"

TEST_F(ConvexHullTest, OrientationTest){
    std::vector<Point> points = {Point(2,0),Point(5,5),Point(0,3),Point(0,0),
                                Point(1,2),Point(0.5,1),Point(0,2)};
    EXPECT_EQ(convex::orientation(points[0],points[1],points[2]), 19);
    EXPECT_EQ(convex::orientation(points[3], points[2], points[0]), -6);
    EXPECT_EQ(convex::orientation(points[4],points[5],points[6]), -1);
}

TEST_F(ConvexHullTest, ConvexHullFunctionTest){
    std::vector<Point> upper;
    std::vector<Point> lower;

    convex::convexHull(diamond,upper,lower);

    std::vector<Point> expectedU = {Point(0,2), Point(3,4), Point(6,2)};
    std::vector<Point> expectedL = {Point(0,2), Point(3,0), Point(6,2)};

    EXPECT_EQ(upper,expectedU);
    EXPECT_EQ(lower, expectedL);

    upper.clear();
    lower.clear();

    convex::convexHull(triangle,upper,lower);

    expectedU.clear();
    expectedL.clear();

    expectedU = {Point(0,0), Point(0,1), Point(1,0)};
    expectedL = {Point(0,0), Point(1,0)};

    EXPECT_EQ(upper,expectedU);
    EXPECT_EQ(lower,expectedL);

    upper.clear();
    lower.clear();

    convex::convexHull(nonconvex,upper,lower);

    expectedU.clear();
    expectedL.clear();

    expectedU = {Point(0,0),Point(1,2),Point(2,0)};
    expectedL = {Point(0,0), Point(2,0)};

    EXPECT_EQ(upper,expectedU);
    EXPECT_EQ(lower,expectedL);
}

TEST_F(ConvexHullTest, RotatingCalipersTest){
    std::vector<std::pair<Point,Point> > diamondRot = convex::rotatingCalipers(diamond);
    std::vector<std::pair<Point,Point> > diamondRes;
    diamondRes.push_back(std::make_pair(Point(0,2),Point(6,2)));
    diamondRes.push_back(std::make_pair(Point(3,4),Point(3,0)));

    EXPECT_EQ(diamondRot,diamondRes);
}

