#include <x-poly/models/hole/PolygonalHole.h>

PolygonalHole::PolygonalHole(std::vector<Point>& p) : Polygon(p) {
    for(int i=0;i<p.size();i++){
        this->points.push_back(p.at(i));
    }
}

Point PolygonalHole::getCenter() {
    return Polygon::getCentroid();
}

