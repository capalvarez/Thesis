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
   return std::to_string(this->getX()) + " " + std::to_string(this->getY());
}

double Point::squareNorm() {
    return pow(this->getX(),2) + pow(this->getY(),2);
}

bool Point::operator==(const Point &other) const{
    return std::abs(this->x-other.x)<0.0001 && std::abs(this->y-other.y)<0.0001;
}

Point3D Point::get3DPoint() {
    return Point3D(this->x, this->y, 0);
}

Vector Point::operator-(Point &other) {
    Point3D* newPoint = new Point3D(this->x - other.getX(), this->y - other.getY(),0);
    return Vector(newPoint);
}
