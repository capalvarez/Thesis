#ifndef THESIS_GEOMETRYFUNCTIONS_H
#define THESIS_GEOMETRYFUNCTIONS_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/PointSegment.h>
#include <vector>

namespace geometry_functions{
    extern double area2(Point p1, Point p2, Point p3);
    extern bool collinear(Point p1, Point p2, Point p3);
    extern bool collinear(PointSegment seg1, PointSegment seg2);
    extern double triangleArea(Point p1, Point p2, Point origin);
    extern double area(std::vector<Point> points, std::vector<int> index);
    extern double area(std::vector<Point> points);
}

#endif
