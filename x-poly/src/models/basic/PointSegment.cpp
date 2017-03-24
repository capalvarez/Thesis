#include <x-poly/models/basic/PointSegment.h>

PointSegment::PointSegment(Point p1, Point p2) : Segment<Point>(p1, p2) {}

double PointSegment::length() {
    return Segment::length(this->p1, this->p2);
}

bool PointSegment::isBoundary(std::vector<Point> p) {
    return this->p1.isInBoundary() && this->p2.isInBoundary();
}

bool PointSegment::contains(Point point) {
    return Segment::contains(point,p1,p2);
}

std::string PointSegment::getString() const {
    return this->getFirst().getString() + " " + this->getSecond().getString();
}

double PointSegment::cartesianAngle() {
    return Segment::cartesianAngle(this->p1, this->p2);
}

bool PointSegment::operator==(const PointSegment other) const {
    return getFirst()==other.getFirst() && getSecond()==other.getSecond() ||
           getFirst()==other.getSecond() && getSecond()==other.getFirst();
}

bool PointSegment::intersection(PointSegment other, Point &inter) {
    return Segment::intersects(this->p1, this->p2, other.getFirst(), other.getSecond(), inter);
}

double PointSegment::perpendicularSlope() {
    double slope = (p2.getY() - p1.getY())/(p2.getX() - p1.getX());

    return -1/slope;
}

bool PointSegment::intersectionInfinite(Point p1, Point p2, Point &inter) {
    return Segment::intersectionInfinite(p1,p2,this->p1, this->p2, inter);
}
