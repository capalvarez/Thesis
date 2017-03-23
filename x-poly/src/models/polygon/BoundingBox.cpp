#include <x-poly/models/polygon/BoundingBox.h>
#include <include/x-poly/models/polygon/Polygon.h>

BoundingBox::BoundingBox(Point p1, Point p2) {
    this->p1 = p1;
    this->p2 = p2;
}

Point BoundingBox::getFirst() const {
    return this->p1;
}

Point BoundingBox::getSecond() const {
    return this->p2;
}

double BoundingBox::getWidth() {
    return std::abs(p1.getX() - p2.getX());
}

double BoundingBox::getHeight() {
    return std::abs(p1.getY() - p2.getY());
}

double BoundingBox::xMin() {
    return std::min(p1.getX(), p2.getX());
}

double BoundingBox::yMin() {
    return std::min(p1.getY(), p2.getY());
}

bool BoundingBox::operator==(const BoundingBox &other) const {
    return getFirst()==other.getFirst() && getSecond()==other.getSecond() ||
           getSecond()==other.getFirst() && getFirst()==other.getSecond();
}

void BoundingBox::getSegments(std::vector<PointSegment> &segments) {
    Point p3 (p2.getX(), p1.getY());
    Point p4 (p1.getX(), p2.getY());

    segments.push_back(PointSegment(p1,p3));
    segments.push_back(PointSegment(p3,p2));
    segments.push_back(PointSegment(p2,p4));
    segments.push_back(PointSegment(p4,p1));
}

bool BoundingBox::fitsInsidePolygon(Polygon poly, Mesh& mesh) {
    bool result = true;
    std::vector<PointSegment> segs;
    this->getSegments(segs);

    for(PointSegment segment: segs){
        result = !poly.intersectsSegment(segment, mesh.getPoints().getList()) && result;
    }

    return result;
}

bool BoundingBox::intersects(BoundingBox box) {
    return false;
}

Point BoundingBox::getClosestTo(Point p) {
    return Point();
}

Point BoundingBox::centroid() {
    return Point();
}
