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
    std::vector<IndexSegment> expectedT = {IndexSegment(0,1), IndexSegment(1,4), IndexSegment(4,0)};
    std::vector<IndexSegment> result;

    triangle->getSegments(result);
    EXPECT_EQ(result,expectedT);
    result.clear();

    std::vector<IndexSegment> expectedS = {IndexSegment(0,1), IndexSegment(1,2), IndexSegment(2,4), IndexSegment(4,0)};
    square->getSegments(result);
    EXPECT_EQ(result,expectedS);
    result.clear();

    std::vector<IndexSegment> expectedN = {IndexSegment(0,1), IndexSegment(1,6), IndexSegment(6,3), IndexSegment(3,5),
                                           IndexSegment(5,0)};
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

TEST_F(PolygonTest, AverageTest){
    EXPECT_EQ(square->getAverageVertex(points), Point(0.5,0.5));
}

TEST_F(PolygonTest, NonConformingTest){
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(2,0), Point(2,1), Point(0,1)};
    std::vector<int> p = {0,1,2,3,4};

    Polygon nonConforming(p,points);
    EXPECT_EQ(nonConforming.getArea(), 2);
    EXPECT_EQ(nonConforming.getCentroid(), Point(1,0.5));
    EXPECT_EQ(nonConforming.getDiameter(), std::sqrt(5));
   // EXPECT_EQ(nonConforming.getAverageVertex(points), Point(1,0.5));
}

TEST_F(PolygonTest, CommonEdgeTest){
    std::vector<int> secondSquarePoints = {1,7,8,2};
    Polygon secondSquare(secondSquarePoints, points);

    EXPECT_EQ(secondSquare.commonEdgesBorder(*square), Pair<int>(2,1));

    std::vector<int> twoEdgesPoints = {9,10,8,2,1,0};
    Polygon twoEdges(twoEdgesPoints, points);

    EXPECT_EQ(twoEdges.commonEdgesBorder(*square), Pair<int>(2,0));
}