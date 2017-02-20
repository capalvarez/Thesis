#ifndef THESIS_TESTCIRCULARHOLE_H
#define THESIS_TESTCIRCULARHOLE_H

#include <gtest/gtest.h>
#include <x-poly/models/Region.h>
#include <x-poly/models/hole/CircularHole.h>

class CircularHoleTest : public ::testing::Test {
protected:
    virtual void SetUp(){
        square = new Region(squarePoints);
        hole = new CircularHole(Point(0.5, 0.5), 0.25);
        square->addHole(hole);
    }

    std::vector<Point> squarePoints = {Point(0,0),Point(1,0),Point(1,1),Point(0,1)};
    Region* square;

    Hole* hole;
};


#endif
