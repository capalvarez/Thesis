#include "Point.h"

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
}

Point::Point() {
    Point(0,0);
}

double Point::getX() const{
    return this->x;
}

double Point::getY() const{
    return this->y;
}

std::string Point::getString() {
   return std::to_string(this->getX()) + " " + std::to_string(this->getY());
}

double Point::squareNorm() {
    return pow(this->getX(),2) + pow(this->getY(),2);
}

bool Point::operator==(const Point &other) const{
    return this->x==other.x && this->y==other.y;
}

Point3D Point::get3DPoint() {
    return Point3D(this->x, this->y, 0);
}

Vector Point::operator-(Point &other) {
    Point3D* newPoint = new Point3D(this->x - other.getX(), this->y - other.getY(),0);
    return Vector(newPoint);
}
