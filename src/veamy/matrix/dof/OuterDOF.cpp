#include <utilities/operations.h>
#include "OuterDOF.h"


OuterDOF::OuterDOF(int i) {
    this->index = i;
}

double OuterDOF::getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p) {
    double xFactor = (points[index].getX() - p.getCentroid().getX())/p.getDiameter();
    double yFactor = (points[index].getY() - p.getCentroid().getY())/p.getDiameter();

    return operations::power(xFactor, coeffs.first)*operations::power(yFactor, coeffs.second);
}

double OuterDOF::laplacianIntegral(Pair<int> poly, Polygon p) {
    return 0;
}



