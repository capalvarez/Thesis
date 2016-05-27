#include "Point3D.h"

class Point3D;

class Vector {
private:
    Point3D* p;
public:
    Vector(Point3D* p);
    ~Vector();

    Point3D* getPoint();
    double norm();
    Vector operator^(Vector v);
};



