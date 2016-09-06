#include <utilities/operations.h>
#include "OuterDOF.h"


OuterDOF::OuterDOF(int i, int p) {
    this->index = i;
    this->point_index = p;
}

double OuterDOF::getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p) {
    double xFactor = (points[point_index].getX() - p.getCentroid().getX())/p.getDiameter();
    double yFactor = (points[point_index].getY() - p.getCentroid().getY())/p.getDiameter();

    return operations::power(xFactor, coeffs.first)*operations::power(yFactor, coeffs.second);
}

double OuterDOF::laplacianIntegral(Pair<int> poly, Polygon p) {
    return 0;
}

int OuterDOF::globalIndex() {
    return this->index;
}

int OuterDOF::pointIndex() {
    return this->point_index;
}






