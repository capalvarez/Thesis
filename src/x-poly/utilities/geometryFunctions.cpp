#include <geometry/Point.h>

namespace geometry_functions{
    double area2(Point p1, Point p2, Point p3){
        Vector v1 = p2.get3DPoint() - p1.get3DPoint();
        Vector v2 = p3.get3DPoint() - p1.get3DPoint();

        return (v1^v2).norm();
    }

    bool collinear(Point p1, Point p2, Point p3){
        //TODO: Check for precision errors here
        return area2(p1,p2,p3)==0;
    }

    double triangleArea(Point p1, Point p2){
        Point origin = *new Point();

        return area2(p1,p2,origin)/2.0;
    }

    double radian(double angle){
        return angle*3.14159265/180;
    }
}

