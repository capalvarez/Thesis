#include <x-poly/models/basic/Point.h>

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

Point::Point() {
    this->x = 0;
    this->y = 0;
}

double Point::getX() const{
    return this->x;
}

double Point::getY() const{
    return this->y;
}

std::string Point::getString() {
    return string_utils::toString<double>(this->getX()) + " " + string_utils::toString<double>(this->getY());
}

double Point::squareNorm() {
    return pow(this->getX(),2) + pow(this->getY(),2);
}

bool Point::operator==(const Point &other) const{
    return std::abs(this->x-other.x)<0.01 && std::abs(this->y-other.y)<0.01;
}

Point3D Point::get3DPoint() {
    return Point3D(this->x, this->y, 0);
}

Vector Point::operator-(Point &other) {
    Point3D* newPoint = new Point3D(this->x - other.getX(), this->y - other.getY(),0);
    return Vector(newPoint);
}

Point Point::operator-(const Point &other) {
    return Point(this->x - other.x, this->y - other.y);
}

bool Point::isInBoundary() {
    return this->isBoundaryPoint;
}

void Point::setBoundary() {
    this->isBoundaryPoint = true;
}

void Point::setX(double newX) {
    this->x = newX;
}

void Point::setY(double newY) {
    this->y = newY;
}

