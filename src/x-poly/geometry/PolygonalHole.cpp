#include "PolygonalHole.h"
#include <utilities/utilities.cpp>

PolygonalHole::PolygonalHole(std::vector<Point> p) : Polygon(utilities::TrivialIndexVector(p.size())) {
    this->points = p;
}

Point PolygonalHole::getCenter() {
    return Polygon::getCentroid(this->points);
}

void PolygonalHole::getSegments(std::vector<Segment> segments) {
    Polygon::getSegments(segments);
}

