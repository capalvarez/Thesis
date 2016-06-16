#include <models/generator/functions.h>
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

