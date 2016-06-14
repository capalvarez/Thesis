#ifndef THESIS_TESTCONVEXHULL_H
#define THESIS_TESTCONVEXHULL_H

#include <gtest/gtest.h>
#include <models/basic/Point.h>
#include <utilities/convexHull.h>
#include <vector>

class ConvexHullTest : public ::testing::Test{
protected:
    virtual void SetUp(){
        diamond = {Point(0,2), Point(3,4), Point(6,2), Point(3,0), Point(2,2), Point(4,1), Point(4,3)};
        triangle = {Point(0,0), Point(1,0), Point(0,1)};
        nonconvex = {Point(0,0), Point(1,1), Point(2,0), Point(1,2)};
    }

    std::vector<Point> diamond;
    std::vector<Point> triangle;
    std::vector<Point> nonconvex;
};


#endif
