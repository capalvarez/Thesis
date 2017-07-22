#ifndef THESIS_TESTPOLYGONALHOLE_H
#define THESIS_TESTPOLYGONALHOLE_H

#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/Region.h>
#include <x-poly/models/hole/PolygonalHole.h>

class PolygonalHoleTest : public ::testing::Test {
protected:
    virtual void SetUp(){
        square = new Region(squarePoints);
        hole = PolygonalHole(holePoints);

        square->addHole(hole);
    }

    std::vector<Point> squarePoints = {Point(0,0),Point(1,0),Point(1,1),Point(0,1)};
    Region* square;

    std::vector<Point> holePoints = {Point(0.25,0.25), Point(0.75,0.25), Point(0.75,0.75), Point(0.25,0.75)};

    Hole hole;
};


#endif
