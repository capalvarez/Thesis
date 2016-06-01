#include "CircularHole.h"
#include "Polygon.h"
#include <utilities/utilities.cpp>


CircularHole::CircularHole(Point p, double r) : Circle(r,p){}

Point CircularHole::getCenter() {
    return this->center;
}

void CircularHole::getSegments(std::vector<Segment> segments) {
    if(this->discrete_points.size()==0){
        discrete_points = discretizeCircle(10);
    }

    Polygon discretePolygon(utilities::TrivialIndexVector(discrete_points.size()));
    discretePolygon.getSegments(segments);
}




