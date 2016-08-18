#ifndef THESIS_TESTDEGREESOFFREEDOM_H
#define THESIS_TESTDEGREESOFFREEDOM_H

#include <gtest/gtest.h>
#include <x-poly/models/polygon/Polygon.h>
#include <matrix/dof/DegreesOfFreedom.h>

class DegreesOfFreedomTest : public ::testing::Test{
protected:
    virtual void SetUp(){
        points = {Point(0,0), Point(1,0), Point(1,1), Point(0,1)};
        std::vector<int> point_index = {0, 1, 2, 3};
        Polygon p (point_index, points);

        degreesSquare = new DegreesOfFreedom(p, 2, points);

    }

    std::vector<Point> points;
    DegreesOfFreedom* degreesSquare;

};


#endif
