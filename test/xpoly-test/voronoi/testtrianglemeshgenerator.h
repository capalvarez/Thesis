#ifndef THESIS_TESTTRIANGLEMESHGENERATOR_H
#define THESIS_TESTTRIANGLEMESHGENERATOR_H

#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/Region.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>

class TriangleMeshGeneratorTest : public ::testing::Test{
protected:
    virtual void SetUp(){
        std::vector<Point> squarePoints = {Point(0,0),Point(1,0),Point(1,1),Point(0,1)};
        square = new Region(squarePoints);

        points = {Point(0.5, 0.5)};

        generator = new TriangleMeshGenerator(points,*square);
    }

    Region* square;
    std::vector<Point> points;
    TriangleMeshGenerator* generator;
};


#endif
