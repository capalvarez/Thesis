#include <x-poly/models/basic/Segment.h>
#include "IntegrationTriangle.h"
#include "gaussQuadrature.cpp"

IntegrationTriangle::IntegrationTriangle(int p1, int p2, int p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

IntegrationTriangle::IntegrationTriangle() {
    this->p1 = -1;
}

int IntegrationTriangle::getFirst() const {
    return this->p1;
}

int IntegrationTriangle::getSecond() const {
    return this->p2;
}

int IntegrationTriangle::getThird() const {
    return this->p3;
}

double IntegrationTriangle::integrate(IntegrationFunction* f, std::vector<Point> points) {
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

        double r = f->call(P,Q);
        result += weight[i]*r;
    }

    return result*jacobian(points)/2;
}


double IntegrationTriangle::jacobian(std::vector<Point> points) {
    Eigen::Matrix2f m;
    m << points[p2].getX() - points[p1].getX(), points[p3].getX() - points[p1].getX(),
            points[p2].getY() - points[p1].getY(), points[p3].getY() - points[p1].getY();

    return m.determinant();
}


bool IntegrationTriangle::operator==(const IntegrationTriangle &other) const {
    return this->p1==other.getFirst() && this->p2==other.getSecond() && this->p3==other.getThird() ||
           this->p2==other.getFirst() && this->p3==other.getSecond() && this->p1==other.getThird() ||
           this->p3==other.getFirst() && this->p1==other.getSecond() && this->p2==other.getThird();
}


bool IntegrationTriangle::isConvex(std::vector<Point> p) {
    double crossPoint = (p[this->p2].getX() - p[this->p1].getX())*(p[this->p3].getY() - p[this->p1].getY()) -
                        (p[this->p2].getY() - p[this->p1].getY())*(p[this->p3].getX() - p[this->p1].getX());
    return crossPoint >= 0;
}

bool IntegrationTriangle::inside(Point p, std::vector<Point> points) {
    double precision = 0.0000001;

    Point a = points[this->p1];
    Point b = points[this->p2];
    Point c = points[this->p3];

    double f = ((b.getY() - c.getY())*(p.getX() - c.getX()) + (c.getX() - b.getX())*(p.getY() - c.getY()))/
               (((b.getY() - c.getY())*(a.getX() - c.getX()) + (c.getX() - b.getX())*(a.getY() - c.getY())) + precision);

    double s = ((c.getY() - a.getY())*(p.getX() - c.getX()) + (a.getX() - c.getX())*(p.getY() - c.getY()))/
		       (((b.getY() - c.getY())*(a.getX() - c.getX()) + (c.getX() - b.getX())*(a.getY() - c.getY())) + precision);

    double t = 1 - f - s;

    return !((f>=1 || f<=0) || (s>=1 || s<=0) || (t>=1 || t<=0)) || inEdges(p, points);
}


bool IntegrationTriangle::inEdges(Point p, std::vector<Point> points) {
    std::vector<Segment> segments = {Segment(p1, p2), Segment(p2, p3), Segment(p3,p1)};

    bool inEdge = false;
    for(int i=0; i<segments.size(); i++){
        inEdge = inEdge || segments[i].contains(points, p);
    }

    return inEdge;
}


bool IntegrationTriangle::isVertex(int i) {
    return this->p1==i || this->p2==i || this->p3==i;
}


bool IntegrationTriangle::isNull() {
    return this->p1<0;
}










