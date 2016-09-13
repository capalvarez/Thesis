#ifndef THESIS_POINTCONSTRAINT_H
#define THESIS_POINTCONSTRAINT_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <unordered_map>
#include "Constraint.h"
#include "structures/mapdata.cpp"

class PointConstraint : public Constraint{
public:
    PointConstraint(Point p, ConstraintDirection d);
    PointConstraint(std::vector<Point> p, ConstraintDirection d);

    void void addToMap(std::unordered_map<Point,int,PointHasher> map);
};


#endif //THESIS_POINTCONSTRAINT_H
