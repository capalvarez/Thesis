#ifndef THESIS_OPERATIONS_H
#define THESIS_OPERATIONS_H
#include <models/polygon/Polygon.h>
#include "Pair.h"

namespace operations{
    extern Pair<double> gradient(Pair<int> polinomial, Polygon p, Point point);
    extern double laplacian(Pair<int> polinomial, Polygon p, Point point);
    extern Pair<double> normal(Point p1, Point p2);
}

#endif
