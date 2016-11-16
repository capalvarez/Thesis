#include <x-poly/models/hole/CircularHole.h>

CircularHole::CircularHole(Point p, double r) : Circle(r, p){
    this->HolePoints = discretizeCircle();
}

Point CircularHole::getCenter() {
    return this->center;
}

void CircularHole::getSegments(std::vector<Segment<int>>& segments, int offset) {
    std::vector<int> indexes;
    utilities::TrivialIndexVector(indexes, (int) this->HolePoints.size());

    Polygon discretePolygon (indexes, this->HolePoints);
    discretePolygon.getSegments(segments, offset);
}








