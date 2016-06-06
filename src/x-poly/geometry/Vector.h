#ifndef THESIS_VECTOR_H
#define THESIS_VECTOR_H

#include "Point3D.h"

class Point3D;

class Vector {
private:
    Point3D* p;
public:
    Vector(Point3D* p);
    ~Vector();

    Point3D* getPoint() const;
    double norm();
    Vector operator^(Vector v);
    bool operator==(const Vector& other) const;
};

#endif


