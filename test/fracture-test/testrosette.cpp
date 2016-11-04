#include <gtest/gtest.h>
#include <fracture/geometry/generator/RosetteGroupGenerator.h>

TEST(RosetteTest, PointsTest){
    std::vector<Point> regionPoints = {Point(0,0), Point(2,0), Point(2,2), Point(0,2)};
    Region region(regionPoints);

    RosetteGroupGenerator rosette(Point(1, 1), 0.2, 22.5, 0, Polygon());
    std::vector<int> polys;
    std::vector<Point> points = rosette.getPoints(0, BreakableMesh());


}