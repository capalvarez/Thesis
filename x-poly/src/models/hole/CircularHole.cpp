#include <x-poly/models/hole/CircularHole.h>

CircularHole::CircularHole(Point p, double r, int grade) : Circle(r,p){
    this->HolePoints = discretizeCircle(grade);
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

std::vector<Point> CircularHole::getPoints() {
    return this->HolePoints;
}







