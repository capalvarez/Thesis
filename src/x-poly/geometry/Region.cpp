#include "Region.h"


Region::Region(std::vector<Point> points) : Polygon(){
    this->points = points;
}

Region::~Region() {}

std::vector<Segment> Region::getSegments() {
    std::vector<Segment> segments;
    int n = points.size();

    for(int i=0;i<n; i++){
        segments.push_back(*new Segment(i%n, (i+1)%n));
    }

    return segments;
}

std::vector<Hole> Region::getHoles() {
    return this->holes;
}


void Region::addHole(Hole h) {
    //TODO: What to do if hole is not inside or intersects region?
    this->holes.push_back(h);
}
