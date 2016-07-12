#include "VEMTriangle.h"
#include "gaussQuadrature.cpp"

VEMTriangle::VEMTriangle(Point p1, Point p2, Point p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

double VEMTriangle::integrate(func_t f) {
    int order = 2;
    double result = 0;

    std::vector<Point> quad_p;
    std::vector<double> weight;

    gauss::gaussQuadrature(order,quad_p,weight);

    for(int i=0;i<weight.size();i++){
        double P = p1.getX() + (p2.getX() - p1.getX())*quad_p[i].getX() + (p3.getX() - p1.getX())*quad_p[i].getY();
        double Q = p1.getY() + (p2.getY() - p1.getY())*quad_p[i].getX() + (p3.getY() - p1.getY())*quad_p[i].getY();

        double r = f(P,Q);
        result += weight[i]*r;
    }

    return result*jacobian()/2;
}


double VEMTriangle::jacobian() {
    Eigen::Matrix2f m;
    m << p2.getX() - p1.getX(), p3.getX() - p1.getX(),
         p2.getY() - p1.getY(), p3.getY() - p1.getY();

    return m.determinant();
}





