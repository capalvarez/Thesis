#include "Region.h"

Region::Region(std::vector<Point>& points) : Polygon(points){
    this->points = points;
}

Region::~Region() {
    std::for_each(holes.begin(), holes.end(), utilities::DeleteVector<Hole*>());
}

std::vector<Hole*> Region::getHoles() {
    return this->holes;
}

void Region::addHole(Hole* h) {
    //TODO: What to do if hole is not inside or intersects region?
    this->holes.push_back(h);
}

void Region::generatePoints(PointGenerator p, int nX, int nY){
    p.generate(this->seedPoints, this->getBox(), nX, nY);
    this->clean();
}

Rectangle Region::getBox() {
    double xMin = LLONG_MAX;
    double xMax = LLONG_MIN;
    double yMin = LLONG_MAX;
    double yMax = LLONG_MIN;

    for(auto& v: points){
        xMin = v.getX()<xMin? v.getX(): xMin;
        xMax = v.getX()>xMax? v.getX(): xMax;
        yMin = v.getY()<yMin? v.getY(): yMin;
        yMax = v.getY()>yMax? v.getY(): yMax;
    }

    return Rectangle(Point(xMin,yMin), Point(xMax,yMax));
}


void Region::clean() {
    for(int i = 0; i<seedPoints.size(); i++){
        if(!containsPoint(points,seedPoints[i])) seedPoints.erase(seedPoints.begin() + i);
    }
}


