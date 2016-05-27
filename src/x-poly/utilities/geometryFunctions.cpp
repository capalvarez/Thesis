#include "Point.h"
#include "Vector.h"

namespace geometry_functions{
    bool collinear(Point p1, Point p2, Point p3){
		

    }

    double triangleArea(Point p1, Point p2){
		Point3D origin = *new Point3D();
        Point3D a = p1.get3DPoint();
		Point3D b = p2.get3DPoint();

    	Vector v1 = b - a;
    	Vector v2 = origin - a;

    	return (v1^v2).norm();
    }

}

