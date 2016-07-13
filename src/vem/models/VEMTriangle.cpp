#include "VEMTriangle.h"
#include "gaussQuadrature.cpp"

VEMTriangle::VEMTriangle(int p1, int p2, int p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

int VEMTriangle::getFirst() const {
    return this->p1;
}

int VEMTriangle::getSecond() const {
    return this->p2;
}

int VEMTriangle::getThird() const {
    return this->p3;
}

double VEMTriangle::integrate(func_t f, std::vector<Point> points) {
    int order = 2;
    double result = 0;

    std::vector<Point> quad_p;
    std::vector<double> weight;

    gauss::gaussQuadrature(order,quad_p,weight);

    Point p1 = points[this->p1];
    Point p2 = points[this->p2];
    Point p3 = points[this->p3];

    for(int i=0;i<weight.size();i++){
        double P = p1.getX() + (p2.getX() - p1.getX())*quad_p[i].getX() + (p3.getX() - p1.getX())*quad_p[i].getY();
        double Q = p1.getY() + (p2.getY() - p1.getY())*quad_p[i].getX() + (p3.getY() - p1.getY())*quad_p[i].getY();

        double r = f(P,Q);
        result += weight[i]*r;
    }

    return result*jacobian(points)/2;
}


double VEMTriangle::jacobian(std::vector<Point> points) {
    Eigen::Matrix2f m;
    m << points[p2].getX() - points[p1].getX(), points[p3].getX() - points[p1].getX(),
            points[p2].getY() - points[p1].getY(), points[p3].getY() - points[p1].getY();

    return m.determinant();
}


bool VEMTriangle::operator==(const VEMTriangle &other) const {
    return this->p1==other.getFirst() && this->p2==other.getSecond() && this->p3==other.getThird() ||
           this->p2==other.getFirst() && this->p3==other.getSecond() && this->p1==other.getThird() ||
           this->p3==other.getFirst() && this->p1==other.getSecond() && this->p2==other.getThird();
}






