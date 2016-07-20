#ifndef THESIS_RECTANGLE_H
#define THESIS_RECTANGLE_H

#include <x-poly/models/basic/Point.h>

class Rectangle {
private:
    Point p1;
    Point p2;
public:
    Rectangle(Point p1, Point p2);

    Point getFirst() const;
    Point getSecond() const;

    double getWidth();
    double getHeight();
    double xMin();
    double yMin();

    bool operator==(const Rectangle& other) const;
};


#endif
