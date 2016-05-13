#include "Point.h"
#include <string>

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
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
    return std::to_string(this->getX()) + " " + std::to_string(this->getY());
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
