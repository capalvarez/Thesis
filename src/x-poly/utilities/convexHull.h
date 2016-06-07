#ifndef THESIS_CONVEXHULL_H
#define THESIS_CONVEXHULL_H

namespace convex {
    extern double orientation(Point p, Point q, Point r);
    extern struct convexHullData convexHull(std::vector<Point> points);
    extern std::vector<std::pair<Point,Point> > rotatingCalipers(std::vector<Point> points);
}
#endif //THESIS_CONVEXHULL_H
