#ifndef THESIS_POINT_H
#define THESIS_POINT_H


#include <bits/stringfwd.h>

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
};


#endif
