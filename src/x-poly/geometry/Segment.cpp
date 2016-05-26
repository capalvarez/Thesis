#include "Segment.h"

Segment::Segment(int p1, int p2) {
    this->p1 = p1;
    this->p2 = p2;
}

Segment::~Segment() {}

int Segment::getFirst() {
    return this->p1;
}

int Segment::getSecond() {
    return this->p2;
}

bool Segment::operator==(Segment &other) {
    return this->p1==other.getFirst() && this->p2==other.getSecond() ||
            this->p2==other.getSecond() && this->p1==other.getFirst();
}
