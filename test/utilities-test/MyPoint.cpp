#include "MyPoint.h"

bool MyPoint::operator==(MyPoint const &rhs) const {
    return this->x==rhs.x && this->y == rhs.y;
}
