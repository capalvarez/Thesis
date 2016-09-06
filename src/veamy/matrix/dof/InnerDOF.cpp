#include "InnerDOF.h"

InnerDOF::InnerDOF(Pair<int> a, int index) {
    this->alpha = a;
    this->index = index;
}

double InnerDOF::getValue(std::vector<Point> points, Pair<int> coeffs, Polygon p) {
    IntegrationPolygon polygon (p.getPoints(), points);

    MaMbFunction* f = new MaMbFunction(coeffs, alpha, p);

    double integral = polygon.integrate(f, points);
    delete(f);

    return integral;
}

double InnerDOF::lineIntegral(int local_id, std::vector<int> elementDOFS, DOFS globalDOFS, int k, Polygon p, std::vector<double> weights, std::vector<Point> points, Pair<int> poly) {
    return 0;
}

double InnerDOF::laplacianIntegral(Pair<int> poly, Polygon p) {
    return -p.getArea()*operations::laplacian(poly,p);
}

int InnerDOF::globalIndex() {
    return this->index;
}

int InnerDOF::pointIndex() {
    //If this is ever required, I deserve the segfault
    return -1;
}







