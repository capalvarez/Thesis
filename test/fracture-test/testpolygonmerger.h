#ifndef THESIS_TESTPOLYGONMERGER_H
#define THESIS_TESTPOLYGONMERGER_H

#include <gtest/gtest.h>
#include <x-poly/models/basic/Point.h>
#include <fracture/geometry/mesh/SimplePolygonMerger.h>

class PolygonMergerTest : public ::testing::Test{
protected:
    virtual void SetUp(){
        points = {Point(0,0), Point(1,0), Point(1,1),Point(0,1), Point(1,2), Point(2,0),
                  Point(2,1), Point(0,2), Point(2,2)};
    }
    
    std::vector<Point> points;

};


#endif 
