#include <iostream>
#include <x-poly/models/Triangulation.h>
#include <vector>

using namespace std;

int main() {
    //Testing writeInFile
    std::vector<Point> region_points;
    Point p1 = *new Point(0,1);
    Point p2 = *new Point(0,0);
    Point p3 = *new Point(1,1);
    Point p4 = *new Point(1,0);

    region_points.push_back(p1);
    //{p1,p2,p3,p4};
    //vector<Point> test_points = {*new Point(0.5,0), *new Point(0,0.5), *new Point(1,0.5), *new Point(0.5,1)};
    //Region* region = new Region(region_points);

    //MeshGenerator* d = new TriangleDelaunayGenerator(test_points,*region);
}