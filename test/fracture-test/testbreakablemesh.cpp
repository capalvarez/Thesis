#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/Region.h>
#include <x-poly/models/generator/functions.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <fracture/geometry/BreakableMesh.h>

TEST(BreakableMeshTest, BreakMeshTest){
    std::vector<Point> squarePoints = {Point(0,0),Point(3,0),Point(3,3),Point(0,3)};
    Region square (squarePoints);

    PointGenerator generator (functions::random_double(0,3), functions::random_double(0,3));

    square.generateSeedPoints(generator, 3, 3);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, square);
    PolygonalMesh mesh = meshGenerator.getMesh();

    BreakableMesh breakableMesh(mesh);

    PointSegment crack(Point(0.25,0.5), Point(2.75,2.5));
    breakableMesh.printInFile("broken.txt");
    int container = breakableMesh.findContainerPolygon(Point(0.25,0.5));

    breakableMesh.breakMesh(container, crack, false, <#initializer#>);
    breakableMesh.printInFile("broken2.txt");
}

TEST(BreakableMeshTest, SwapPolygonsTest){
    std::unordered_map<IndexSegment, int, SegmentHasher> m;
    std::vector<Point> squarePoints = {Point(0,0),Point(3,0),Point(3,3),Point(0,3)};
    Region square (squarePoints);

    PointGenerator generator (functions::uniform(1), functions::uniform(1));

    square.generateSeedPoints(generator, 3, 3);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, square);
    PolygonalMesh mesh = meshGenerator.getMesh();

    BreakableMesh breakableMesh(mesh);

    breakableMesh.swapPolygons(0, 8, m);


    breakableMesh.printInFile("testMesh.txt");
}

TEST(BreakableMeshTest, MergePolygonsTest){
    std::vector<Point> squarePoints = {Point(0,0),Point(3,0),Point(3,3),Point(0,3)};
    Region square (squarePoints);

    PointGenerator generator (functions::random_double(0,3), functions::random_double(0,3));

    square.generateSeedPoints(generator, 9, 9);
    std::vector<Point> seeds = square.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, square);
    PolygonalMesh mesh = meshGenerator.getMesh();
    mesh.printInFile("randomMerge.txt");

    BreakableMesh breakableMesh(mesh);
    std::vector<int> polys = {16,6,7,0};
    breakableMesh.mergePolygons(polys);
    breakableMesh.printInFile("randomMerge2.txt");

}

TEST(BreakableMeshTest, MergePolygonsListTest){
    std::vector<Point> points = {Point(0,0), Point(2,0), Point(2,1), Point(0,1)};
    Region region(points);
    region.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 7, 7);

    std::vector<Point> seeds = region.getSeedPoints();
    TriangleMeshGenerator g(seeds, region);
    PolygonalMesh m = g.getMesh();
    BreakableMesh breakableMesh(m);
    breakableMesh.printInFile("testMesh.txt");

    std::vector<int> polys = {23,28,33,32,13,12,6,14,24};

    breakableMesh.mergePolygons(polys);
    breakableMesh.printInFile("testMesh2.txt");

}