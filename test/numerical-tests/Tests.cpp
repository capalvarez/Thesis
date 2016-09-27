#include "Tests.h"

Tests::Tests() {
    /*One Square*/
    std::vector<Point> points = {Point(0,0), Point(1,0), Point(0,1), Point(1,1)};
    std::vector<int> p ={0,1,2,3};

    std::vector<Polygon> polygons = {Polygon(p,points)};
    std::vector<Segment> segments;

    one_square = Mesh(points,polygons,segments);

    /*Hundred Square*/
    std::vector<Point> hundred_square_points = {Point(0, 0), Point(20, 0), Point(20, 5), Point(0, 5)};
    Region region(hundred_square_points);
    PointGenerator generator_uniform (functions::uniform(1), functions::uniform(1));

    region.generatePoints(generator_uniform, 20, 5);
    std::vector<Point> seeds = region.getSeedPoints();

    TriangleMeshGenerator meshGenerator(seeds, region);
    hundred_square = meshGenerator.getMesh();

    /*Random Voronoi on (0,1) square*/
    Region region1(points);
    PointGenerator generator_random(functions::random_double(0,1), functions::random_double(0,1));

    region1.generatePoints(generator_random, 10, 10);
    seeds = region1.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, region1);
    random_voronoi_square = meshGenerator.getMesh();

    /*Rectangle hole with squares*/
    Hole* circle = new CircularHole(Point(0.5,0.5),0.1);
    region1.addHole(circle);

    region1.generatePoints(generator_uniform, 10, 10);
    seeds = region1.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, region1);
    rectangle_hole = meshGenerator.getMesh();

    /*Trapezoid*/
    std::vector<Point> trapezoid_points = {Point(0,0), Point(10,3), Point(10,7), Point(0,10)};
    Region trapezoid_region (trapezoid_points);

    trapezoid_region.generatePoints(generator_uniform, 10, 10);
    seeds = trapezoid_region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, trapezoid_region);
    trapezoid = meshGenerator.getMesh();

    /*L shape*/
    std::vector<Point> l_points = {Point(10,0), Point(20,0), Point(20,20), Point(0,20), Point(0,10), Point(10,10)};
    Region l_region(l_points);

    l_region.generatePoints(generator_uniform, 10, 10);
    seeds = l_region.getSeedPoints();

    meshGenerator = TriangleMeshGenerator(seeds, l_region);
    L = meshGenerator.getMesh();
}








