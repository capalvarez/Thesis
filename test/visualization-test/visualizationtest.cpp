#include <string>
#include <x-poly/models/Region.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <x-poly/models/hole/CircularHole.h>
#include <x-poly/models/generator/functions.h>

void generateTest(std::string testName, Region r, std::vector<Point> points){
    TriangleMeshGenerator g(points, r);
    Triangulation t = g.getDelaunayTriangulation();
    t.print(testName + "_triangles.txt");

    PolygonalMesh m = g.getMesh();
    m.printInFile(testName + ".txt");
}

int main(){
    std::vector<Point> square_points = {Point(0,0), Point(10,0), Point(10,10), Point(0,10)};
    Region square(square_points);

    std::vector<Point> romboid_points = {Point(0,0), Point(10,0), Point(15,10), Point(5,10)};
    Region romboid(romboid_points);

    std::vector<Point> quarter_circle_points = {Point(0,0), Point(10,0), Point(10,10)};

    double max = 10.0;
    for(int i=0; i<max;i++){
        double angle = 90 - (90/max)*i;

        double x = 10 - 10*std::cos(utilities::radian(angle));
        double y = 10*std::sin(utilities::radian(angle));

        Point point (x, y);

        quarter_circle_points.push_back(point);
    }

    Region quarter_circle(quarter_circle_points);

    std::vector<Point> unicorn_points = {Point(2,0), Point(3,0.5), Point(3.5,2), Point(4,4), Point(6,4), Point(8.5,4),
                                         Point(9,2), Point(9.5,0.5), Point(10,0), Point(10.5,0.5), Point(11.2,2.5),
                                         Point(11.5,4.5), Point(11.8,8.75), Point(11.8,11.5), Point(13.5,11), Point(14.5,11.2),
                                         Point(15,12), Point(15,13), Point(15,14.5), Point(14,16.5), Point(15,19.5), Point(15.2,20),
                                         Point(14.5,19.7), Point(11.8,18.2), Point(10.5,18.3), Point(10,18), Point(8,16),
                                         Point(7.3,15.3), Point(7,13.8), Point(6.7,11.5), Point(3.3,11.3), Point(1,10.5),
                                         Point(0.4,8.8), Point(0.3,6.8), Point(0.4,4), Point(0.8,2.1), Point(1.3,0.4)};
    Region unicorn(unicorn_points);

    /*----------------Random generation--------------------------------------------------------------------*/
    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 5, 5);
    generateTest("squareRandom5", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    generateTest("squareRandom10", square, square.getSeedPoints());
    square.printInFile("square.txt");
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 20, 20);
    generateTest("squareRandom20", square, square.getSeedPoints());
    square.cleanSeedPoints();

    romboid.generateSeedPoints(PointGenerator(functions::random_double(0,15), functions::random_double(0,15)), 5, 5);
    generateTest("romboidRandom5", romboid, romboid.getSeedPoints());
    romboid.printInFile("romboid.txt");
    romboid.cleanSeedPoints();

    romboid.generateSeedPoints(PointGenerator(functions::random_double(0,15), functions::random_double(0,15)), 10, 10);
    generateTest("romboidRandom10", romboid, romboid.getSeedPoints());
    romboid.cleanSeedPoints();

    quarter_circle.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 5, 5);
    generateTest("quarter_circleRandom5", quarter_circle, quarter_circle.getSeedPoints());
    quarter_circle.printInFile("quarter_circle.txt");
    quarter_circle.cleanSeedPoints();

    quarter_circle.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    generateTest("quarter_circleRandom10", quarter_circle, quarter_circle.getSeedPoints());
    quarter_circle.cleanSeedPoints();

    unicorn.generateSeedPoints(PointGenerator(functions::random_double(0,15), functions::random_double(0,20)), 5, 5);
    generateTest("unicornRandom5", unicorn, unicorn.getSeedPoints());
    unicorn.cleanSeedPoints();

    unicorn.generateSeedPoints(PointGenerator(functions::random_double(0,15), functions::random_double(0,20)), 10, 10);
    generateTest("unicornRandom10", unicorn, unicorn.getSeedPoints());
    unicorn.printInFile("unicorn.txt");
    unicorn.cleanSeedPoints();

    /*-----------------------------------------------Uniform generation-------------------------------------------------*/
    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest("squareUniform10", square, square.getSeedPoints());
    square.cleanSeedPoints();

    romboid.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest("romboidUniform10", romboid, romboid.getSeedPoints());
    romboid.cleanSeedPoints();

    quarter_circle.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest("quarter_circleUniform10", quarter_circle, quarter_circle.getSeedPoints());
    quarter_circle.cleanSeedPoints();

    unicorn.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest("unicornUniform10", unicorn, unicorn.getSeedPoints());
    unicorn.cleanSeedPoints();

    /*---------------------------------------Generation with holes------------------------------------*/
    Hole circular = CircularHole(Point(5,5), 2);
    square.addHole(circular);
    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 5, 5);
    generateTest("squareHoleCenterRandom5", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    generateTest("squareHoleCenterRandom10", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest("squareHoleCenterUniform10", square, square.getSeedPoints());
    square.cleanSeedPoints();
    square.printInFile("SquareHole.txt");

    square = Region(square_points);

    circular = CircularHole(Point(5,10), 2);
    square.addHole(circular);
    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 5, 5);
    generateTest("squareHoleBorderRandom5", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    generateTest("squareHoleBorderRandom10", square, square.getSeedPoints());
    square.cleanSeedPoints();

    square.generateSeedPoints(PointGenerator(functions::constant(), functions::constant()), 10, 10);
    generateTest("squareHoleBorderUniform10", square, square.getSeedPoints());
    square.cleanSeedPoints();

    Hole circular1 = CircularHole(Point(10,5), 2);
    Hole circular2 = CircularHole(Point(5,0), 2);
    Hole circular3 = CircularHole(Point(0,5), 2);
    square.addHole(circular1);
    square.addHole(circular2);
    square.addHole(circular3);
    square.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    generateTest("squareSwissCheeseRandom10", square, square.getSeedPoints());
    square.cleanSeedPoints();

    circular = CircularHole(Point(10,0), 4);
    quarter_circle.addHole(circular);
    quarter_circle.generateSeedPoints(PointGenerator(functions::random_double(0,10), functions::random_double(0,10)), 10, 10);
    generateTest("quarter_circleHoleRandom10", quarter_circle, quarter_circle.getSeedPoints());
    quarter_circle.cleanSeedPoints();

    Hole circle = CircularHole(Point(8,8), 2);
    unicorn.addHole(circle);
    unicorn.generateSeedPoints(PointGenerator(functions::random_double(0,15), functions::random_double(0,20)), 10, 10);
    generateTest("unicornHoleInsideRandom10", unicorn, unicorn.getSeedPoints());
    unicorn.cleanSeedPoints();

    unicorn.cleanInternalHoles();
    circle = CircularHole(Point(5,5), 2);
    unicorn.addHole(circle);
    unicorn.generateSeedPoints(PointGenerator(functions::random_double(0,15), functions::random_double(0,20)), 10, 10);
    generateTest("unicornHoleBorderRandom10", unicorn, unicorn.getSeedPoints());
    unicorn.cleanSeedPoints();


}