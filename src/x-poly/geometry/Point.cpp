#include "Point.h"
#include <string>
#include <utilities/utilities.cpp>

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

Point::Point() {
    this->x = 0;
    this->y = 0;
}

Point::~Point() {}

double Point::getX() {
    return this->x;
}

double Point::getY() {
    return this->y;
}

void Point::setX(double x) {
    this->x = x;
}

void Point::setY(double y) {
    this->y = y;
}

std::string Point::getString() {
   return utilities::ToString(this->getX()) + " " + utilities::ToString(this->getY());
}

double Point::getBoundaryMarker() {
    return 0;
}

double Point::squareNorm() {
    return 0;
}

bool Point::operator==(const Point &other) {
    return false;
}

Point3D Point::get3DPoint() {
    return Point3D(this->x, this->y, 0);
}
