#include "testpolygon.h"

TEST_F(PolygonTest, AreaTest){
    EXPECT_EQ(triangle->getArea(),0.5);
    EXPECT_EQ(square->getArea(),1);
    EXPECT_EQ(nonconvex->getArea(),1.5);
}

TEST_F(PolygonTest, IsConvexTest){
    EXPECT_TRUE(triangle->isConvex(points));
    EXPECT_EQ(square->isConvex(points), true);
    EXPECT_EQ(nonconvex->isConvex(points), false);
}

TEST_F(PolygonTest, GetSegmentsTest){
    std::vector<Segment> expectedT = {Segment(0,1), Segment(1,4), Segment(4,0)};
    std::vector<Segment> result;

    triangle->getSegments(result);
    EXPECT_EQ(result,expectedT);
    result.clear();

    std::vector<Segment> expectedS = {Segment(0,1), Segment(1,2), Segment(2,4), Segment(4,0)};
    square->getSegments(result);
    EXPECT_EQ(result,expectedS);
    result.clear();

    std::vector<Segment> expectedN = {Segment(0,1), Segment(1,6), Segment(6,3), Segment(3,5), Segment(5,0)};
    nonconvex->getSegments(result);
    EXPECT_EQ(result,expectedN);
}


TEST_F(PolygonTest, InEdgesTest){
    EXPECT_TRUE(triangle->inEdges(points,points[0]));
    EXPECT_FALSE(triangle->inEdges(points,Point(0.75,0.4)));

    EXPECT_TRUE(square->inEdges(points,Point(0,0)));
    EXPECT_FALSE(square->inEdges(points, Point(0.5,0.5)));
    EXPECT_TRUE(square->inEdges(points,Point(0.6,1)));
}

TEST_F(PolygonTest, ContainsPointTest){
    Point p1 (0.25,0.25);
    Point p2 (0.75,0.4);
    Point p3(0.5,0.5);
    Point p4 (1,1);
    Point p5(0.5,1.5);
    Point p6 (0.25,1.5);

    EXPECT_TRUE(triangle->containsPoint(points,p1));
    EXPECT_FALSE(triangle->containsPoint(points,p2));
    EXPECT_TRUE(triangle->containsPoint(points,p3));
    EXPECT_TRUE(triangle->containsPoint(points, points[0]));
    EXPECT_FALSE(triangle->containsPoint(points,p4));

    EXPECT_TRUE(square->containsPoint(points,p1));
    EXPECT_TRUE(square->containsPoint(points,p2));
    EXPECT_TRUE(square->containsPoint(points,p3));
    EXPECT_TRUE(square->containsPoint(points,p4));
    EXPECT_FALSE(square->containsPoint(points,p5));

    EXPECT_FALSE(nonconvex->containsPoint(points,p5));
    EXPECT_TRUE(nonconvex->containsPoint(points,p6));
}

TEST_F(PolygonTest, SignedAreaTest){
    EXPECT_EQ(triangle->signedArea(points),0.5);
    EXPECT_EQ(square->signedArea(points),1);
    EXPECT_EQ(nonconvex->signedArea(points),1.5);
}

TEST_F(PolygonTest, CentroidTest){
    EXPECT_EQ(triangle->getCentroid(), Point(1.0/3,1.0/3));
    EXPECT_EQ(square->getCentroid(), Point(0.5,0.5));
    EXPECT_EQ(nonconvex->getCentroid(), Point(4.5/9,7.0/9));
}

TEST_F(PolygonTest, DiameterTest){
    EXPECT_EQ(triangle->getDiameter(),sqrt(2));
    EXPECT_EQ(square->getDiameter(),sqrt(2));
    EXPECT_EQ(nonconvex->getDiameter(),sqrt(5));
}

TEST_F(PolygonTest, IsClockwise){
    EXPECT_FALSE(triangle->isClockwise(points));
    EXPECT_FALSE(square->isClockwise(points));
    EXPECT_TRUE(nonclockwise->isClockwise(points));
}