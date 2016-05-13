#include "Hole.h"

Hole::Hole(Point center) : center(center) {
    this->center = *new Point(0,0);
}

Hole::~Hole() {

}

Point Hole::getCenter() {
    return Point(0, 0);
}
