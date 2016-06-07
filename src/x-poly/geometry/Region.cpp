#include "Region.h"

Region::Region(std::vector<Point> points) : Polygon(utilities::TrivialIndexVector(points.size()), points){
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
