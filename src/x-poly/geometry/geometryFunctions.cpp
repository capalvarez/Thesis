#include "Point.h"

namespace geometry_functions{
    Point calculateCircumcenter(Point p1, Point p2, Point p3) {
        double d = 2*(p1.getX()*(p2.getY() - p3.getY()) + p2.getX()*(p3.getY() - p1.getY()) +
                      p3.getX()*(p1.getY() - p2.getY()));

        double uX = (p1.squareNorm()*(p2.getY() - p3.getY()) + p2.squareNorm()*(p3.getY() - p1.getY()) + p3.squareNorm()*(p1.getY() - p2.getY()))/d;
        double uY = (p1.squareNorm()*(p3.getX() - p2.getX()) + p2.squareNorm()*(p1.getX() - p3.getX()) + p3.squareNorm()*(p2.getX() - p1.getX()))/d;

        return *new Point(uX,uY);
    }
}

