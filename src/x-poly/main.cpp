#include <iostream>
#include "models/basic/Point.h"
#include "models/Region.h"
#include <vector>
#include <voronoi/MeshGenerator.h>
#include <voronoi/TriangleMeshGenerator.h>


using namespace std;

int main() {
    //Testing writeInFile
    std::vector<Point> region_points = {Point(0,1), Point(0,0), Point(1,0), Point(1,1)};

    vector<Point> test_points = {Point(0.5,0), Point(0,0.5), Point(1,0.5), Point(0.5,1)};
    Region region(region_points);

    MeshGenerator* d = new TriangleMeshGenerator(test_points, region);
}