#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>

TEST(MeshTest, FindPolygonTest) {
    std::vector<Point> squarePoints = {Point(0,0),Point(1,0),Point(1,1),Point(0,1)};
    Region square(squarePoints);
    std::vector<Point> points1 = {Point(0.5, 0.5)};

    TriangleMeshGenerator gen (points1,square);
    Mesh m = gen.getMesh();

    int p1 = m.findContainerPolygon(Point(0.5,0.5));
    int p2 = m.findContainerPolygon(Point(0.1,0.1));





}
