#include <x-poly/models/hole/CircularHole.h>

CircularHole::CircularHole(Point p, double r) : Circle(r,p){}

Point CircularHole::getCenter() {
    return this->center;
}

void CircularHole::getSegments(std::vector<Segment> segments) {
    if(this->discrete_points.size()==0){
        discrete_points = discretizeCircle(10);
    }

    std::vector<int> indexes;
    utilities::TrivialIndexVector(indexes, discrete_points.size());
    Polygon discretePolygon (indexes, this->discrete_points);
    discretePolygon.getSegments(segments);
}




