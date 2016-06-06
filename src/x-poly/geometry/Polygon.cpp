#include "Polygon.h"
#include "utilities/geometryFunctions.cpp"
#include <utilities/convexHull.cpp>

Polygon::Polygon(std::vector<int> points, std::vector<Point> p) {
    this->points = points;

    std::vector<Point> this_points;
    for(int i=0;i<points.size();i++){
        this_points.push_back(p[points[i]]);
    }

    this->diameter = this->calculateDiameter(this_points);
    this->area = this->calculateArea(p);
    this->centroid = this->calculateCentroid(p);
}

Polygon::~Polygon() {}

double Polygon::calculateDiameter(std::vector<Point> p) {
    std::vector<std::pair<Point,Point>> rotatingCalipers = convex::rotatingCalipers(p);
    double max = -1;

    for(int i=0;i<rotatingCalipers.size();i++){
        double distance = (rotatingCalipers[i].first - rotatingCalipers[i].second).norm();
        if(distance>max){
            max = distance;
        }
    }

    return max;
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

}

bool Polygon::containsPoint(std::vector<Point> p, Point point) {
    int j = points.size() - 1 ;
    bool oddNodes = false;

    for (int i=0; i<points.size(); i++) {
        Point pI = p[points[i]];
        Point pJ = p[points[j]];

        if (pI.getY()<=point.getY() && pJ.getY()>=point.getY()
            || pJ.getY()<=point.getY() && pI.getY()>=point.getY()) {

            if (pI.getX() + (point.getY()-pI.getY())/(pJ.getY()-pI.getY())*(pJ.getX()-pI.getX())<point.getX()){
                oddNodes=!oddNodes;
            }
        }
        j = i;
    }

    return oddNodes || inEdges(p,point);
}

bool Polygon::inEdges(std::vector<Point> p, Point point) {
    std::vector<Segment> segments;
    this->getSegments(segments);

    bool inEdge = false;
    for(int i=0; i<segments.size(); i++){
        inEdge = inEdge || segments[i].contains(p,point);
    }

    return inEdge;
}

bool Polygon::isConvex(std::vector<Point> p) {
    int n = p.size();

    double determinant = convex::orientation(p[0],p[1],p[2]);

    for(int i=1;i<n; i++){
        double newResult = convex::orientation(p[i],p[(i+1)%n],p[(i+2)%n]);

        if(determinant*newResult<0){
            return false;
        }
    }

    return true;
}
