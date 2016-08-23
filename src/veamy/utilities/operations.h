#ifndef THESIS_OPERATIONS_H
#define THESIS_OPERATIONS_H
#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>
#include "Pair.h"

namespace operations{
    extern Pair<double> gradient(Pair<int> polinomial, Polygon p, Point point);
    extern double laplacian(Pair<int> polinomial, Polygon p);
    extern double power(double base, double exp);
    extern int kronecker(int i, int j);
}

#endif
