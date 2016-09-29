#include <x-poly/models/basic/Point3D.h>

double Point3D::getX() const {
    return this->x;
}

double Point3D::getY() const {
    return this->y;
}

double Point3D::getZ() const {
    return this->z;
}

Point3D::Point3D(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point3D::Point3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector Point3D::operator-(Point3D p) {
    return Vector(new Point3D(this->x - p.getX(), this->y - p.getY(), this->z - p.getZ()));
}


bool Point3D::operator==(const Point3D &other) const {
    return this->x == other.getX() && this->y == other.getY() && this->z == other.getZ();
}

