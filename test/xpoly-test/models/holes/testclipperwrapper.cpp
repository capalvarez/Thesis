#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/hole/clipper/lib/clipper.hpp>
#include <x-poly/models/hole/clipper/ClipperWrapper.h>

TEST(ClipperWrapperTest, PolygonUnionTest){
    std::vector<Point> points = {Point(0,0),Point(1,0),Point(2,0),Point(2,1),Point(1,1),Point(0,1)};
    std::vector<int> poly1 = {0,1,4,5};
    std::vector<int> poly2 = {1,2,3,4};

    std::vector<Polygon> polys = {Polygon(poly1, points), Polygon(poly2, points)};





}