#include "CircularHole.h"

CircularHole::CircularHole(Point p, double r) {
    this->center = p;
    this->radius = r;
}

CircularHole::~CircularHole() {}

Point CircularHole::getCenter() {
    return this->center;
}


std::vector<Segment*> CircularHole::getSegments() {
    return std::vector<Segment*>();
}
