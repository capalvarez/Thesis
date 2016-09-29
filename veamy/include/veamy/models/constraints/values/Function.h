#ifndef THESIS_FUNCTION_H
#define THESIS_FUNCTION_H

#include <x-poly/models/basic/Point.h>
#include "ConstraintValue.h"

typedef double(*func_t)(double, double);

class Function : public ConstraintValue{
private:
    func_t f;
public:
    Function(func_t f);

    double getValue(Point p);
};


#endif