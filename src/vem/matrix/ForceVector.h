#ifndef THESIS_FORCEVECTOR_H
#define THESIS_FORCEVECTOR_H

#include <x-poly/models/polygon/Polygon.h>
#include <x-poly/models/basic/Point.h>

class ForceVector {


public:
    ForceVector(Polygon p, std::vector<Point> points);
};


#endif
