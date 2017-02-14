#include <x-poly/models/hole/PolygonalHole.h>

PolygonalHole::PolygonalHole(std::vector<Point>& p) : Polygon(p) {
    for(int i=0;i<p.size();i++){
        this->HolePoints.push_back(p.at(i));
    }
}

Point PolygonalHole::getCenter() {
    return Polygon::getCentroid();
}

void PolygonalHole::getSegments(std::vector<IndexSegment> &s, int offset) {
    Polygon::getSegments(s, offset);
}



