#include "Polygon.h"
#include "utilities/geometryFunctions.cpp"

double Polygon::area(std::vector<Point> p){
    double area = 0.0;
    int n = this->points.size(); 

    for(int i=0; i !=n; i++) {
        area += geometry_functions::triangleArea(p[this->points[i%n]],p[this->points[(i+1)%n]]);
    }

    return area;
}


double Polygon::diameter(std::vector<Point> p) {
    return 0;
}

Point Polygon::getCentroid(std::vector<Point> p) {
    return Point(0, 0);
}

double Polygon::signedArea(std::vector<Point> p) {
    return 0;
}
