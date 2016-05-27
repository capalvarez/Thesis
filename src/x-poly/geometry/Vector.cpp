#include "Vector.h"
#include <math.h>

Vector::Vector(Point3D* p) {
    this->p = p;
}

Vector::~Vector() {}

double Vector::norm() {
    return sqrt(pow(this->p->getX(),2) + pow(this->p->getY(),2) + pow(this->p->getZ(),2));
}

Point3D* Vector::getPoint() {
    return this->p;
}

Vector Vector::operator^(Vector v) {
    Point3D* newPoint = new Point3D(this->p->getY()*v.getPoint()->getZ() - this->p->getZ()*v.getPoint()->getY(),
                                    this->p->getZ()*v.getPoint()->getX() - this->p->getX()*v.getPoint()->getZ(),
                                    this->p->getX()*v.getPoint()->getY() - this->p->getY()*v.getPoint()->getX());

    return Vector(newPoint);
}

