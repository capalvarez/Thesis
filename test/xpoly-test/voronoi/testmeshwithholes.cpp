#include <vector>
#include <x-poly/models/hole/PolygonalHole.h>
#include <x-poly/models/hole/Hole.h>
#include <gtest/gtest.h>
#include <x-poly/models/Region.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <x-poly/models/hole/CircularHole.h>

/*TEST(MeshWithHolesTest, PolygonalHoleTest){
    std::vector<Point> rPoints = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    Region square(rPoints);

    std::vector<Point> hPoints = {Point(0.25,0.25), Point(0.75,0.25), Point(0.75,0.75), Point(0.25,0.75)};
    Hole* h = new PolygonalHole(hPoints);

    square.addHole(h);

    std::vector<Point> points = {Point(0.5,0), Point(1,0.5), Point(0.5,1), Point(0,0.5)};

    TriangleMeshGenerator g(points, square);
    Triangulation t = g.getDelaunayTriangulation();
    t.writeInFile("hole.txt");

    Mesh m = g.getMesh();
    m.printInFile("h.txt");
}*/

TEST(MeshWithHolesTest, PolygonalHoleInBorderTest){
    /*std::vector<Point> rPoints = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    Region square(rPoints);

    std::vector<Point> hPoints = {Point(0.25,0.75), Point(0.75,0.75), Point(0.75,1), Point(0.25,1)};
    Hole* h = new PolygonalHole(hPoints);

    square.addHole(h);

    std::vector<Point> points = {Point(0.5,0), Point(1,0.5), Point(0,0.5)};

    TriangleMeshGenerator g(points, square);
    Triangulation t = g.getDelaunayTriangulation();
    t.writeInFile("hole.txt");

    Mesh m = g.getMesh();
    m.printInFile("h.txt");*/
}

TEST(MeshWithHolesTest, PolygonalHoleCompletelyInBorderTest){
   /* std::vector<Point> rPoints = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    Region square(rPoints);

    std::vector<Point> hPoints = {Point(0.75,0.75), Point(1,0.75), Point(1,1), Point(0.75,1)};
    Hole* h = new PolygonalHole(hPoints);

    square.addHole(h);

    std::vector<Point> points = {Point(0.5,0), Point(1,0.5), Point(0.5,1), Point(0,0.5)};

    TriangleMeshGenerator g(points, square);
    Triangulation t = g.getDelaunayTriangulation();
    t.writeInFile("hole.txt");

    Mesh m = g.getMesh();
    m.printInFile("h.txt");
*/
}

TEST(MeshWithHolesTest, PolygonalHoleBiggerTest){
    /*std::vector<Point> rPoints = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    Region square(rPoints);

    std::vector<Point> hPoints = {Point(0,0), Point(2,0), Point(2,2), Point(0,2)};
    Hole* h = new PolygonalHole(hPoints);

    square.addHole(h);
    std::vector<Point> points;

    TriangleMeshGenerator g(points, square);
    Triangulation t = g.getDelaunayTriangulation();
    t.writeInFile("hole.txt");

    Mesh m = g.getMesh();
    m.printInFile("h.txt");*/
}

TEST(MeshWithHolesTest, PolygonalHoleHalfTest){
    std::vector<Point> rPoints = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    Region square(rPoints);

    std::vector<Point> hPoints = {Point(0.5,0), Point(1,0), Point(1,1), Point(0.5,1)};
    Hole* h = new PolygonalHole(hPoints);

    square.addHole(h);
    std::vector<Point> points;

    TriangleMeshGenerator g(points, square);
    Triangulation t = g.getDelaunayTriangulation();
    t.writeInFile("hole.txt");

    Mesh m = g.getMesh();
    m.printInFile("h.txt");
}

TEST(MeshWithHolesTest, CircularHoleInsideTest){
   /*std::vector<Point> rPoints = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    Region square(rPoints);

    Hole* h = new CircularHole(Point(0.5,0.5),0.25,20);

    square.addHole(h);
    std::vector<Point> points = {Point(0.5,0), Point(1,0.5), Point(0.5,0), Point(0,0.5)};

    TriangleMeshGenerator g(points, square);
    Triangulation t = g.getDelaunayTriangulation();
    t.writeInFile("hole.txt");

    Mesh m = g.getMesh();
    m.printInFile("h.txt");*/
}

TEST(MeshWithHolesTest, CircularHoleBorderTest){
/*    std::vector<Point> rPoints = {Point(0, 0), Point(1, 0), Point(1, 1), Point(0, 1)};
    Region square(rPoints);

    Hole *h = new CircularHole(Point(0.5, 1), 0.25, 20);

    square.addHole(h);
    std::vector<Point> points;

    TriangleMeshGenerator g(points, square);
    Triangulation t = g.getDelaunayTriangulation();
    t.writeInFile("hole.txt");

    Mesh m = g.getMesh();
    m.printInFile("h.txt");*/
}