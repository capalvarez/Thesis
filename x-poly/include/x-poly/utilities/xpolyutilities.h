#ifndef THESIS_XPOLYUTILITIES_H
#define THESIS_XPOLYUTILITIES_H

#include <vector>
#include <iostream>
#include <x-poly/models/basic/Point.h>

namespace xpoly_utilities {
    extern void TrivialIndexVector(std::vector<int>& index_vector, int n);
    extern double radian(double angle);
    extern double degrees(double angle);
    extern double crossProduct(Point a, Point b);
    extern double norm(Point p);
}
#endif