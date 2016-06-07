#include "PolygonalHole.h"


PolygonalHole::PolygonalHole(std::vector<Point> p) : Polygon(utilities::TrivialIndexVector(p.size()), p) {
    this->points = p;
}

Point PolygonalHole::getCenter() {
    return Polygon::getCentroid();
}

