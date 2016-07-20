#ifndef THESIS_TESTTRIANGLEMESHGENERATOR_H
#define THESIS_TESTTRIANGLEMESHGENERATOR_H

#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/Region.h>
#include <x-poly/voronoi/TriangleMeshGenerator.h>
#include <x-poly/models/Mesh.h>
#include <x-poly/models/Triangulation.h>

class TriangleMeshGeneratorTest : public ::testing::Test{
protected:
    virtual void SetUp(){
        std::vector<Point> squarePoints = {Point(0,0),Point(1,0),Point(1,1),Point(0,1)};
        square = new Region(squarePoints);

        std::vector<Point> pentagonPoints = {Point(6,0), Point(12,4), Point(7,7), Point(1,7), Point(0,2)};
        pentagon = new Region(pentagonPoints);

        points1 = {Point(0.5, 0.5)};

        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                points2.push_back(Point(0.25*i,0.25*j));
            }
        }

        points_border = {Point(0.5,0), Point(1,0.5), Point(0.5,1), Point(0,0.5)};
        random_points = {Point(0.117326,0.141106), Point(0.176638,0.850197), Point(0.496491,0.226596),
                         Point(0.732736,0.344643), Point(0.529896,0.128436), Point(0.988603,0.802724),
                         Point(0.892638,0.491170), Point(0.244295,0.942909), Point(0.555867,0.072324)};

        pentagonPoints = {Point(6,4)};

        //square_gen = new TriangleMeshGenerator(points1,*square);
        square_gen2 = new TriangleMeshGenerator(random_points,*square);
        //square_gen_borders = new TriangleMeshGenerator(points_border,*square);
        //pentagon_gen = new TriangleMeshGenerator(pentagonPoints,*pentagon);
    }

    Region* square;
    Region* pentagon;

    std::vector<Point> points1;
    std::vector<Point> points2;
    std::vector<Point> points_border;
    std::vector<Point> pentagon_points;
    std::vector<Point> random_points;

    TriangleMeshGenerator* square_gen;
    TriangleMeshGenerator* square_gen2;
    TriangleMeshGenerator* square_gen_borders;
    TriangleMeshGenerator* pentagon_gen;
};


#endif
