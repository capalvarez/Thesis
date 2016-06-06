#include "PolygonalHole.h"
#include <utilities/utilities.cpp>

PolygonalHole::PolygonalHole(std::vector<Point> p) : Polygon(utilities::TrivialIndexVector(p.size()), p) {
    this->points = p;
}

Point PolygonalHole::getCenter() {
    return Polygon::getCentroid();
}

void PolygonalHole::getSegments(std::vector<Segment> segments) {
    Polygon::getSegments(segments);
}

