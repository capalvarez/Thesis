#ifndef THESIS_POINTCONSTRAINT_H
#define THESIS_POINTCONSTRAINT_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <unordered_map>
#include <models/constraints/values/ConstraintValue.h>
#include "Constraint.h"
#include "models/constraints/structures/mapdata.h"

class PointConstraint : public Constraint{
private:
    //TODO: Check if the user repeats constrained_points
    std::vector<Point> constraints;
    ConstraintValue* v;
public:
    PointConstraint(Point p, Direction d, ConstraintValue* value);
    PointConstraint(std::vector<Point> p, Direction d, ConstraintValue* value);

    double getValue(Point p);
};


#endif
