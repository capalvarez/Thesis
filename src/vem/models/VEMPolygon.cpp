#include "VEMPolygon.h"

VEMPolygon::VEMPolygon(std::vector<int> index, std::vector<Point> points) : Polygon(index,points){

}

std::vector<VEMTriangle> VEMPolygon::triangulate(std::vector<VEMTriangle>& triangles, std::vector<Point>& p) {

    return triangles;
}

double VEMPolygon::getAverage(func_t f, std::vector<Point> points) {
    double result = 0;
    std::vector<VEMTriangle> triangles;
    triangulate(triangles, points);

    for(int i=0;i<triangles.size();i++){
        result += triangles[i].integrate(f, points);
    }

    return result;
}


VEMTriangle VEMPolygon::getEar(std::vector<Point> points) {
    return VEMTriangle(0, 0, 0);
}

