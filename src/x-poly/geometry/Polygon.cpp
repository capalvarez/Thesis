#include "Polygon.h"

double Polygon::area(std::vector<Point> p){
    double area = 0.0;
    int n = this->points.size(); 

    for(int i=0; i !=n; i++) {
        area += triangleArea(p[this->points[i%n]],p[this->points[(i+1)%n]]);
    }

    return area;
}

