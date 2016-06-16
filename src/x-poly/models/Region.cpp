#include "Region.h"

Region::Region(std::vector<Point>& points) : Polygon(points){
    this->p = points;
}

Region::~Region() {
    std::for_each(holes.begin(), holes.end(), utilities::DeleteVector<Hole*>());
}

std::vector<Hole*> Region::getHoles() {
    return this->holes;
}


std::vector<Point> Region::getSeedPoints() {
    return this->seedPoints;
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

    for(auto& v: p){
        xMin = v.getX()<xMin? v.getX(): xMin;
        xMax = v.getX()>xMax? v.getX(): xMax;
        yMin = v.getY()<yMin? v.getY(): yMin;
        yMax = v.getY()>yMax? v.getY(): yMax;
    }

    return Rectangle(Point(xMin,yMin), Point(xMax,yMax));
}


void Region::clean() {
    std::vector<int> toKeep;
    std::vector<Point> newSeeds;

    for(int i = 0; i<seedPoints.size(); i++){
        if(containsPoint(p,seedPoints[i])) toKeep.push_back(i);
    }

    for(int i=0; i<toKeep.size(); i++){
        newSeeds.push_back(seedPoints[toKeep[i]]);
    }

    this->seedPoints = newSeeds;
}


