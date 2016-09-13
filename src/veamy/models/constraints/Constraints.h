#ifndef THESIS_CONSTRAINTS_H
#define THESIS_CONSTRAINTS_H

#include <x-poly/models/basic/Point.h>
#include <unordered_map>
#include "Constraint.h"
#include "structures/mapdata.cpp"

class Constraints {
private:
    std::unordered_map<Point, int, PointHasher> constraints;
public:
    Constraints();
    void addConstraint(Constraint* c);
    bool isConstrained(Point p);
};


#endif
