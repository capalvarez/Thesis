#ifndef THESIS_CONVEXHULL_H
#define THESIS_CONVEXHULL_H

#include <x-poly/models/basic/Point.h>

namespace convex {
    extern double orientation(Point p, Point q, Point r);
    extern void convexHull(std::vector<Point> points, std::vector<Point>& u, std::vector<Point>& l);
    extern std::vector<std::pair<Point,Point> > rotatingCalipers(std::vector<Point> points);
}
#endif
