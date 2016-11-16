#include <x-poly/models/basic/Vector.h>

Vector::Vector(Point3D* p) {
    this->p = p;
}

Vector::~Vector() {}

double Vector::norm() {
    return std::sqrt(std::pow(this->p->getX(),2) + std::pow(this->p->getY(),2) + std::pow(this->p->getZ(),2));
}

Point3D* Vector::getPoint() const{
    return this->p;
}

Vector Vector::operator^(Vector v) {
    Point3D* newPoint = new Point3D(this->p->getY()*v.getPoint()->getZ() - this->p->getZ()*v.getPoint()->getY(),
                                    this->p->getZ()*v.getPoint()->getX() - this->p->getX()*v.getPoint()->getZ(),
                                    this->p->getX()*v.getPoint()->getY() - this->p->getY()*v.getPoint()->getX());

    return Vector(newPoint);
}

bool Vector::operator==(const Vector &other) const {
    return *this->p == *other.getPoint();
}


