#include <iostream>
#include "src/x-poly/delaunay/DelaunayGenerator.h"
#include "src/x-poly/geometry/Point.h"
#include "src/x-poly/delaunay/TriangleDelaunayGenerator.h"

using namespace std;

int main() {
    //Testing writeInFile
    vector<Point> region_points {*new Point(0,0), *new Point(1,1), *new Point(0,1), *new Point(1,0)};
    vector<Point> test_points = {*new Point(0.5,0), *new Point(0,0.5), *new Point(1,0.5), *new Point(0.5,1)};
    Region* region = new Region(region_points);

    DelaunayGenerator* d = new TriangleDelaunayGenerator(test_points,*region);
}