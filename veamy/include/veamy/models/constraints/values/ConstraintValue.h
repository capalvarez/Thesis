#ifndef VEAMY_CONSTRAINTVALUE_H
#define VEAMY_CONSTRAINTVALUE_H

#include <x-poly/models/basic/Point.h>

class ConstraintValue {
public:
    virtual double getValue(Point p) = 0;
};

#endif
