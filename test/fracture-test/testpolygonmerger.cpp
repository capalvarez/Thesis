#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <fracture/geometry/mesh/SimplePolygonMerger.h>

TEST(PolygonMergerTest, MergePolygonsTest){
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(1,1),Point(0,1), Point(1,2), Point(2,0),
                                 Point(2,1)};
    std::vector<int> square1Points = {0,1,2,3};
    std::vector<int> square2Points = {1,5,6,2};

    std::vector<int> expected = {2,3,0,1,5,6};

    Polygon square1 (square1Points, points);
    Polygon square2 (square2Points, points);

    SimplePolygonMerger merger;
    Polygon p = merger.mergePolygons(square1, square2, points);

    EXPECT_EQ(p, Polygon(expected, points));

}