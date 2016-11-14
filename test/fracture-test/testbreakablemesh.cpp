#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/Region.h>
#include <x-poly/models/generator/functions.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <fracture/geometry/BreakableMesh.h>

TEST(BreakableMeshTest, BreakMeshTest){
    std::vector<Point> squarePoints = {Point(0,0),Point(3,0),Point(3,3),Point(0,3)};
    Region square (squarePoints);

    PointGenerator generator (functions::uniform(1), functions::uniform(1));

    square.generatePoints(generator, 3, 3);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, square);
    Mesh mesh = meshGenerator.getMesh();

    BreakableMesh breakableMesh(mesh);
    Polygon& poly = breakableMesh.getPolygon(2);

    Segment<Point> crack(Point(0.25,1.5), Point(2.75,1.5));

    breakableMesh.breakMesh(2, crack);

    breakableMesh.printInFile("broken.txt");
}

TEST(BreakableMeshTest, SwapPolygonsTest){
    std::vector<Point> squarePoints = {Point(0,0),Point(3,0),Point(3,3),Point(0,3)};
    Region square (squarePoints);

    PointGenerator generator (functions::uniform(1), functions::uniform(1));

    square.generatePoints(generator, 3, 3);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, square);
    Mesh mesh = meshGenerator.getMesh();

    BreakableMesh breakableMesh(mesh);

    breakableMesh.swapPolygons(0,8);


    breakableMesh.printInFile("testMesh.txt");
}

TEST(BreakableMeshTest, MergePolygonsTest){
    std::vector<Point> squarePoints = {Point(0,0),Point(3,0),Point(3,3),Point(0,3)};
    Region square (squarePoints);

    PointGenerator generator (functions::uniform(1), functions::uniform(1));

    square.generatePoints(generator, 3, 3);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, square);
    Mesh mesh = meshGenerator.getMesh();

    BreakableMesh breakableMesh(mesh);

    breakableMesh.printInFile("testMesh1.txt");

    breakableMesh.mergePolygons(0,1);
    breakableMesh.printInFile("testMesh.txt");
    breakableMesh.getSegments().printInFile("edges.txt");
}