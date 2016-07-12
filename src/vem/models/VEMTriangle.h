#ifndef THESIS_TRIANGLE_H
#define THESIS_TRIANGLE_H

#include <x-poly/models/polygon/Triangle.h>
#include <x-poly/models/basic/Point.h>
#include <lib/Eigen/Dense>

typedef double(*func_t)(double, double);

class VEMTriangle {
private:
    Point p1;
    Point p2;
    Point p3;

    double jacobian();
public:
    VEMTriangle(Point p1, Point p2, Point p3);
    double integrate(func_t f);
};


#endif //THESIS_TRIANGLE_H
