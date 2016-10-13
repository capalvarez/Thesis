#include <string>
#include <x-poly/models/Region.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <x-poly/models/hole/CircularHole.h>
#include <x-poly/models/generator/functions.h>

int main();

void generateTest(std::string testName, Region r, Hole* h, std::vector<Point> points){
    r.addHole(h);

    TriangleMeshGenerator g(points, r);
    Triangulation t = g.getDelaunayTriangulation();
    t.writeInFile(testName + "_triangles.txt");

    Mesh m = g.getMesh();
    m.printInFile(testName + ".txt");
}

void generateTestNoHole(std::string testName, Region r, std::vector<Point> points){
    TriangleMeshGenerator g(points, r);
    Triangulation t = g.getDelaunayTriangulation();
    t.writeInFile(testName + "_triangles.txt");

    Mesh m = g.getMesh();
    m.printInFile(testName + ".txt");
}

int run(){
    std::vector<Point> square_points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
    Region square(square_points);

    std::vector<Point> inside_p = {Point(0.25,0.25), Point(0.75,0.25), Point(0.75,0.75), Point(0.25,0.75)};
    Hole* inside = new PolygonalHole(inside_p);

    std::vector<Point> points = {Point(0.5,0), Point(1,0.5), Point(0.5,1), Point(0,0.5)};

    generateTest("PolygonalInside", square, inside, points);

    /*------------------------------------------------------------------------------------------------------*/

    std::vector<Point> hPoints = {Point(0.25,0.75), Point(0.75,0.75), Point(0.75,1), Point(0.25,1)};
    Hole* border = new PolygonalHole(hPoints);

    points = {Point(0.5,0), Point(1,0.5), Point(0,0.5)};

    generateTest("PolygonalBorder", square, inside, points);

    /*------------------------------------------------------------------------------------------------------*/

    hPoints = {Point(0.75,0.75), Point(1,0.75), Point(1,1), Point(0.75,1)};
    Hole* completely_inside = new PolygonalHole(hPoints);

    points = {Point(0.5,0), Point(1,0.5), Point(0.5,1), Point(0,0.5)};

    generateTest("PolygonalHoleCompletelyInBorder", square, completely_inside, points);

    /*------------------------------------------------------------------------------------------------------*/

    hPoints = {Point(0.5,0), Point(1,0), Point(1,1), Point(0.5,1)};
    Hole* half = new PolygonalHole(hPoints);

    points = {};

    generateTest("PolygonalHoleHalfTest", square, half, points);

    /*-----------------------------------------------------------------------------------------------------*/
    Hole* circle = new CircularHole(Point(0.5,0.5),0.25,20);
    points = {Point(0.5,0), Point(1,0.5), Point(0.5,0), Point(0,0.5)};

    generateTest("CircularHoleInside", square, circle, points);

    /*-----------------------------------------------------------------------------------------------------*/

    border = new CircularHole(Point(0.5, 1), 0.25, 20);
    points = {};

    generateTest("CircularHoleBorderTest", square, border, points);

    /*------------------------------------------------------------------------------------------------------*/
    std::vector<Point> personPoints = {Point(0,0),Point(3,0),Point(3,2),Point(4.5,2),Point(4.5,0),Point(8.5,0),Point(8.5,1),
                                       Point(6,1),Point(6,5),Point(7,5),Point(7,3.5),Point(9,3.5),Point(9,7),Point(5,7),
                                       Point(5,8.5),Point(4,8.5),Point(4,7),Point(2,7),Point(2,10),Point(0,10),Point(0,8),
                                       Point(1,8),Point(1,6),Point(3,6),Point(3,3),Point(1.5,3),Point(1.5,1),Point(0,1)};
    Region person(personPoints);
    generateTestNoHole("PersonTest", person, points);

    /*---------------------------------------------------------------------------------------------------*/
    std::vector<Point> unicornPoints = {Point(0,3),Point(3,1),Point(5,5),Point(4.5,4),Point(7,6),Point(7,0),Point(17,5),
                                        Point(14,5),Point(14,6),Point(15,6.5),Point(13,6.25),Point(12,7),Point(14,8),
                                        Point(11,7.5),Point(10,9),Point(11,10),Point(9,9.25),Point(7,9.5),Point(6,11),
                                        Point(6,9.5),Point(5,9.4),Point(4,13),Point(5,11.5),Point(0,14),Point(8,2),
                                        Point(7,1),Point(7,2)};
    Region unicorn(unicornPoints);
    generateTestNoHole("UnicornTest", unicorn, points);

    /*-------------------------------------------------------------------------------------------------*/
    square.generatePoints(PointGenerator(functions::random_double(0,1),functions::random_double(0,1)), 10, 10);
    generateTestNoHole("RandomTest", square, square.getSeedPoints());

}