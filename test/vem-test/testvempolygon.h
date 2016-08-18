#ifndef THESIS_TESTVEMPOLYGON_H
#define THESIS_TESTVEMPOLYGON_H

#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <models/integration/IntegrationPolygon.h>
#include "testfunctions/testfunctions.h"

class VEMPolygonTest : public ::testing::Test{
protected:
    virtual void SetUp(){
        points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1), Point(0.5,0.5)};
        std::vector<int> index = {0,1,2,3};
        std::vector<int> index2 = {0,1,4,2,3};

        square = new IntegrationPolygon(index,points);
        nonconvex = new IntegrationPolygon(index2,points);
    }

    std::vector<Point> points;
    IntegrationPolygon* square;
    IntegrationPolygon* nonconvex;
};

#endif
