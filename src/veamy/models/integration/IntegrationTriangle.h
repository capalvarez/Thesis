#ifndef THESIS_TRIANGLE_H
#define THESIS_TRIANGLE_H

#include <x-poly/models/polygon/Triangle.h>
#include <x-poly/models/basic/Point.h>
#include <lib/Eigen/Dense>

typedef double(*func_t)(double, double);

class IntegrationTriangle{
private:
    int p1;
    int p2;
    int p3;

    double jacobian(std::vector<Point> points);
    bool inEdges(Point p, std::vector<Point> points);
public:
    IntegrationTriangle(int p1, int p2, int p3);
    IntegrationTriangle();

    int getFirst() const;
    int getSecond() const;
    int getThird() const;

    bool isNull();

    double integrate(func_t f, std::vector<Point> points);
    bool operator==(const IntegrationTriangle& other) const;
    bool isConvex(std::vector<Point> points);
    bool inside(Point p, std::vector<Point> points);
    bool isVertex(int i);
};


#endif //THESIS_TRIANGLE_H
