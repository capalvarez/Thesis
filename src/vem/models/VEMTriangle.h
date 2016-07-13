#ifndef THESIS_TRIANGLE_H
#define THESIS_TRIANGLE_H

#include <x-poly/models/polygon/Triangle.h>
#include <x-poly/models/basic/Point.h>
#include <lib/Eigen/Dense>

typedef double(*func_t)(double, double);

class VEMTriangle {
private:
    int p1;
    int p2;
    int p3;

    double jacobian(std::vector<Point> points);
public:
    VEMTriangle(int p1, int p2, int p3);

    int getFirst() const;
    int getSecond() const;
    int getThird() const;

    double integrate(func_t f, std::vector<Point> points);
    bool operator==(const VEMTriangle& other) const;
};


#endif //THESIS_TRIANGLE_H
