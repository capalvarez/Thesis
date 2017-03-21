#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <x-poly/models/generator/functions.h>

TEST(MeshTest, FindPolygonTest) {
    std::vector<Point> squarePoints = {Point(0,0),Point(1,0),Point(1,1),Point(0,1)};
    Region square(squarePoints);
    std::vector<Point> points1 = {Point(0.5, 0.5)};

    TriangleMeshGenerator gen (points1,square);
    PolygonalMesh m = gen.getMesh();

    EXPECT_EQ(m.findContainerPolygon(Point(0.5,0.5)), 2);
    EXPECT_EQ(m.findContainerPolygon(Point(0.1,0.1)), 1);
    EXPECT_EQ(m.findContainerPolygon(Point(0,0.25)), 1);
    EXPECT_EQ(m.findContainerPolygon(Point(0,0)), 1);
}

TEST(MeshTest, GetAllNeighboursTest){
    std::vector<Point> points = {Point(0,0), Point(2,0), Point(2,1), Point(0,1)};
    Region region(points);
    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 7, 7);

    std::vector<Point> seeds = region.getSeedPoints();
    TriangleMeshGenerator g(seeds, region);
    PolygonalMesh m = g.getMesh();
    Triangulation t = g.getDelaunayTriangulation();

    UniqueList<int> neighbours = m.getAllNeighbours(24);
    std::vector<int> expected = {23,28,33,32,13,12,6,14};
    EXPECT_EQ(neighbours.getList(), expected);
}