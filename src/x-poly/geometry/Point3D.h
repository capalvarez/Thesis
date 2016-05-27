#include "Vector.h"

class Point3D {
private:
    double x;
    double y;
    double z;
public:
    Point3D(double x, double y, double z);
    Point3D();
    ~Point3D();

    double getX();
    double getY();
    double getZ();

    Vector operator-(Point3D p);
};


