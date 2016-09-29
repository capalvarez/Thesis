#include <x-poly/models/basic/Segment.h>

Segment::Segment(int p1, int p2) {
    this->p1 = p1;
    this->p2 = p2;
}


Segment::Segment(const Segment &other) {
    this->p1 = other.p1;
    this->p2 = other.p2;
}

Segment::Segment() {}


int Segment::getFirst() const{
    return this->p1;
}

int Segment::getSecond() const{
    return this->p2;
}

bool Segment::operator==(const Segment other) const{
    return getFirst()==other.getFirst() && getSecond()==other.getSecond() ||
           getFirst()==other.getSecond() && getSecond()==other.getFirst();
}

bool Segment::contains(std::vector<Point>& p, Point point) {
    Point p1 = p[this->p1];
    Point p2 = p[this->p2];

    return  ((point.getX()>=p1.getX() && point.getX()<=p2.getX()) || (point.getX()>=p2.getX() && point.getX()<=p1.getX())) &&
            ((point.getY()>=p1.getY() && point.getY()<=p2.getY()) || (point.getY()>=p2.getY() && point.getY()<=p1.getY())) &&
            std::abs(p1.getX()*(p2.getY()-point.getY()) + p2.getX()*(point.getY()-p1.getY()) + point.getX()*(p1.getY()-p2.getY()))<0.0001;
}

Point Segment::middlePoint(std::vector<Point> p) {
    return Point((p[this->p1].getX() + p[this->p2].getX())/2, (p[this->p1].getY() + p[this->p2].getY())/2);
}


std::string Segment::getString() {
    return std::to_string(this->p1) + " " + std::to_string(this->p2);
}


