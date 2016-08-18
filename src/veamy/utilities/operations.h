#ifndef THESIS_OPERATIONS_H
#define THESIS_OPERATIONS_H
#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>
#include "Pair.h"

namespace operations{
    extern double polyDerivate(double base, double exp);
    extern Pair<double> gradient(Pair<int> polinomial, Polygon p, Point point);
    extern double laplacian(Pair<int> polinomial, Polygon p, Point point);
    extern double power(double base, double exp);
}

#endif
