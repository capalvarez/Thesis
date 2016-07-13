#ifndef THESIS_TESTREGION_H
#define THESIS_TESTREGION_H

#include <gtest/gtest.h>
#include <x-poly/models/Region.h>

class RegionTest: public ::testing::Test {
protected:
    virtual void SetUp(){
        std::vector<Point> rectanglePoints = {Point(0,0), Point(10,0),Point(10,10),Point(0,10)};
        std::vector<Point> nonconvexPoints = {Point(0,0), Point(10,0),Point(10,10),Point(0,10), Point(5,5)};
        std::vector<Point> polygonPoints = {Point(3,0),Point(10,2),Point(7,5),Point(8,10),Point(3,7),
                                            Point(2,8),Point(0,4)};

        rectangle = new Region(rectanglePoints);
        nonconvex = new Region(nonconvexPoints);
        polygon = new Region(polygonPoints);
    }

    Region* rectangle;
    Region* nonconvex;
    Region* polygon;
};


#endif //THESIS_TESTREGION_H
