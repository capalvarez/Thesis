#include <bits/stringfwd.h>
#include "Point3D.h"

class Point {
private:
    double x;
    double y;
public:
    Point(double x, double y);
    ~Point();

    double getX();
    double getY();
    double getBoundaryMarker();
    void setX(double x);
    void setY(double y);

    double squareNorm();
    std::string getString();
    bool operator==(const Point& other);

    Point3D get3DPoint();
};

