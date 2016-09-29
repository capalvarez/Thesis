#include "testregion.h"

TEST_F(RegionTest, BoxTest){
    Rectangle box (Point(0,0),Point(10,10));

    EXPECT_EQ(rectangle->getBox(),box);
    EXPECT_EQ(nonconvex->getBox(),box);
    EXPECT_EQ(polygon->getBox(),box);
}

TEST_F(RegionTest, GeneratePointsTest){
    std::vector<Point> rectangleRes = {Point(0,0),Point(5,0),Point(10,0),Point(0,5),Point(5,5),Point(10,5),
                                       Point(0,10),Point(5,10),Point(10,10)};

    rectangle->generatePoints(PointGenerator(functions::constant(),functions::constant()),3,3);
    EXPECT_EQ(rectangleRes,rectangle->getSeedPoints());

    std::vector<Point> nonconvexRes = {Point(0,0),Point(5,0),Point(10,0),Point(5,5),Point(10,5),
                                      Point(0,10),Point(5,10),Point(10,10)};
    nonconvex->generatePoints(PointGenerator(functions::constant(),functions::constant()),3,3);
    EXPECT_EQ(nonconvexRes,nonconvex->getSeedPoints());

    std::vector<Point> polygonRes = {Point(5,5)};
    polygon->generatePoints(PointGenerator(functions::constant(),functions::constant()),3,3);
    EXPECT_EQ(polygonRes,polygon->getSeedPoints());
}

TEST_F(RegionTest, AddHoleTest){
    std::vector<Point> hPoints = {Point(2,0), Point(7,0), Point(7,2), Point(2,2)};
    Hole* h = new PolygonalHole(hPoints);

    rectangle->addHole(h);
    std::vector<Point> expected = {Point(7,2), Point(7,0), Point(10,0), Point(10,10), Point(0,10),
                                   Point(0,0), Point(2,0), Point(2,2)};
    EXPECT_EQ(rectangle->getRegionPoints(), expected);
}

TEST_F(RegionTest, AddHoleInsideTest){
    std::vector<Point> hPoints = {Point(4,4), Point(6,4), Point(6,6), Point(4,6)};
    Hole* h = new PolygonalHole(hPoints);

    rectangle->addHole(h);
    std::vector<Point> expected = {Point(0,0), Point(10,0), Point(10,10), Point(0,10), Point(4,4), Point(6,4),
                                   Point(6,6), Point(4,6)};
    EXPECT_EQ(rectangle->getRegionPoints(), expected);
}

