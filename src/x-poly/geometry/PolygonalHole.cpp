#include "PolygonalHole.h"
#include <utilities/utilities.cpp>

PolygonalHole::PolygonalHole(std::vector<Point> p) : Polygon(utilities::TrivialIndexVector(p.size())) {
    this->points = p;
}

Point PolygonalHole::getCenter() {
    return getCentroid(this->points);
}


std::vector<Segment *> PolygonalHole::getSegments() {
    return std::vector<Segment*>();
}
