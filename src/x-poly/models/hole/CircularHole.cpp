#include "CircularHole.h"
#include "models/polygon/Polygon.h"

CircularHole::CircularHole(Point p, double r) : Circle(r,p){
    this->HolePoints = discretizeCircle(4);
}

Point CircularHole::getCenter() {
    return this->center;
}

void CircularHole::getSegments(std::vector<Segment>& segments, int offset) {
    std::vector<int> indexes;
    utilities::TrivialIndexVector(indexes, (int) this->HolePoints.size());

    Polygon discretePolygon (indexes, this->HolePoints);
    discretePolygon.getSegments(segments);
}


std::vector<Point> CircularHole::getPoints() {
    return std::vector<Point>();
}






