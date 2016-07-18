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

        std::vector<Point> pentagonPoints = {Point(6,0), Point(12,4), Point(7,7), Point(1,7), Point(0,2)};
        pentagon = new Region(pentagonPoints);

        points1 = {Point(0.5, 0.5)};

        for(int i=1;i<4;i++){
            for(int j=1;j<4;j++){
                points2.push_back(Point(0.25*i,0.25*j));
            }
        }

        pentagonPoints = {Point(6,4)};

        //square_gen = new TriangleMeshGenerator(points1,*square);
        square_gen2 = new TriangleMeshGenerator(points2,*square);
        //pentagon_gen = new TriangleMeshGenerator(pentagonPoints,*pentagon);
    }

    Region* square;
    Region* pentagon;

    std::vector<Point> points1;
    std::vector<Point> points2;
    std::vector<Point> pentagon_points;

    TriangleMeshGenerator* square_gen;
    TriangleMeshGenerator* square_gen2;
    TriangleMeshGenerator* pentagon_gen;
};


#endif
