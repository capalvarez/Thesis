#ifndef THESIS_OPERATIONS_H
#define THESIS_OPERATIONS_H
#include <models/polygon/Polygon.h>

namespace operations{
    extern std::pair<double,double> gradient(std::pair<int,int> polinomial, Polygon p, Point point);
    extern double laplacian(std::pair<int, int> polinomial, Polygon p, Point point);
    extern double dot(std::pair<double, double> v1, std::pair<double, double> v2);
    extern std::pair<double,double> normal(Point p1, Point p2);
}

#endif
