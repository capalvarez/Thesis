#include <x-poly/models/Region.h>
#include <x-poly/models/generator/functions.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <fracture/geometry/BreakableMesh.h>
#include "testpolygonmerger.h"

TEST_F(PolygonMergerTest, TwoSquaresTest){
    std::vector<int> square1Points = {0,1,2,3};
    std::vector<int> square2Points = {1,5,6,2};

    std::vector<int> expected = {2,3,0,1,5,6};

    Polygon square1 (square1Points, points);
    Polygon square2 (square2Points, points);

    SimplePolygonMerger merger;
    Polygon p = merger.mergePolygons(square1, square2, points);

    EXPECT_EQ(p, Polygon(expected, points));
}

TEST_F(PolygonMergerTest, LAndSquareTest){
    std::vector<int> squarePoints = {0,1,2,3};
    std::vector<int> LPoints = {1,5,8,7,3,2};

    std::vector<int> expected = {2,3,0,1,5,6};

    Polygon square (squarePoints, points);
    Polygon L (LPoints, points);

    SimplePolygonMerger merger;
    Polygon p = merger.mergePolygons(square, L, points);

    EXPECT_EQ(p, Polygon(expected, points));
}

TEST_F(PolygonMergerTest, InMeshTest){
    std::vector<Point> points = {Point(0,0), Point(2,0), Point(2,1), Point(0,1)};
    Region region(points);
    region.generatePoints(PointGenerator(functions::constant(), functions::constant()), 2, 2);

    std::vector<Point> seeds = region.getSeedPoints();
    TriangleMeshGenerator g(seeds, region);
    PolygonalMesh m = g.getMesh();

    BreakableMesh mesh(m);
    mesh.mergePolygons(0,1);

    mesh.printInFile("merged.txt");
}