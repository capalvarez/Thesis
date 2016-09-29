#ifndef THESIS_INTEGRATIONTRIANGLE_H
#define THESIS_INTEGRATIONTRIANGLE_H

#include <x-poly/models/polygon/Triangle.h>
#include <x-poly/models/basic/Point.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/matrix/integration/IntegrationFunction.h>

#include <x-poly/models/basic/Segment.h>
#include <veamy/matrix/integration/gaussQuadrature.h>


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

    double integrate(IntegrationFunction* f, std::vector<Point> points);
    bool operator==(const IntegrationTriangle& other) const;
    bool isConvex(std::vector<Point> points);
    bool inside(Point p, std::vector<Point> points);
    bool isVertex(int i);
};


#endif
