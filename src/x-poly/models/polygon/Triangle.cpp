#include "Triangle.h"

Triangle::Triangle(std::vector<int> points, std::vector<Point>& p) : Polygon(points, p) {}

Point Triangle::getCircumcenter(std::vector<Point>& p) {
    Point A = p[this->points[0]];
    Point B = p[this->points[1]];
    Point C = p[this->points[2]];

    double d = 2*(A.getX()*(B.getY() - C.getY()) + B.getX()*(C.getY() - A.getY()) + C.getX()*(A.getY() - B.getY()));

    double uX = (A.squareNorm()*(B.getY() - C.getY()) + B.squareNorm()*(C.getY() - A.getY()) + C.squareNorm()*(A.getY() - B.getY()))/d;
    double uY = (A.squareNorm()*(C.getX() - B.getX()) + B.squareNorm()*(A.getX() - C.getX()) + C.squareNorm()*(B.getX() - A.getX()))/d;

    return Point(uX,uY);
}


