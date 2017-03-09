#include <x-poly/models/basic/PointSegment.h>

PointSegment::PointSegment(Point p1, Point p2) : Segment<Point>(p1, p2) {}

double PointSegment::length() {
    return std::sqrt(std::pow(this->p1.getX() - this->p2.getX(), 2) + std::pow(this->p1.getY() - this->p2.getY(),2));
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
