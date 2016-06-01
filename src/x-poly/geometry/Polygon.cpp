#include "Polygon.h"
#include "utilities/geometryFunctions.cpp"

Polygon::Polygon(std::vector<int> points, std::vector<Point> p) {
    this->points = points;

    this->diameter = this->calculateDiameter(p);
    this->area = this->calculateArea(p);
    this->centroid = this->calculateCentroid(p);
}

Polygon::~Polygon() {}

double Polygon::calculateDiameter(std::vector<Point> p) {
    return 0;
}

double Polygon::calculateArea(std::vector<Point> p) {
    double area = 0.0;
    int n = this->points.size();

    for(int i=0; i !=n; i++) {
        area += geometry_functions::triangleArea(p[this->points[i%n]],p[this->points[(i+1)%n]]);
    }

    return area;
}


double Polygon::getArea(){
    return this->area;
}

double Polygon::getDiameter() {
    return this->diameter;
}

Point Polygon::getCentroid() {
   return this->centroid;
}

double Polygon::signedArea(std::vector<Point> p) {
    return 0;
}

void Polygon::getSegments(std::vector<Segment> segments) {
    int n = this->points.size();

    for(int i=0;i<n; i++){
        segments.push_back(*new Segment(i%n, (i+1)%n));
    }
}


Point Polygon::calculateCentroid(std::vector<Point> p) {
    return Point();
}

bool Polygon::containsPoint(Point point) {
    return false;
}


