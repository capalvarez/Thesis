#include <models/Point.h>
#include <models/Segment.h>
#include <gtest/gtest.h>
#include <models/Polygon.h>
#include <vector>

class PolygonTest: public ::testing::Test{
protected:
    virtual void SetUp(){
        points = {Point(0,0), Point(1,0), Point(1,1), Point(0.5,1),
                  Point(0,1), Point(0,2), Point(1,2)};

        std::vector<int> t = {0,1,4};
        triangle = new Polygon(t,points);

        std::vector<int> s = {0,1,2,4};
        square = new Polygon(s,points);

        std::vector<int> n = {0,1,6,3,5};
        nonconvex = new Polygon(n,points);
    }

    std::vector<Point> points;

    Polygon* triangle;
    Polygon* square;
    Polygon* nonconvex;
};
