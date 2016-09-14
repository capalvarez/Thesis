#ifndef THESIS_CONSTANT_H
#define THESIS_CONSTANT_H

#include <x-poly/models/basic/Point.h>
#include "ConstraintValue.h"

class Constant : public ConstraintValue{
private:
    double value;
public:
    Constant(double val);

    double getValue(Point p);
};


#endif
