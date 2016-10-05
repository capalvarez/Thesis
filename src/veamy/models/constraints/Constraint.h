#ifndef THESIS_POINTCONSTRAINT_H
#define THESIS_POINTCONSTRAINT_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <unordered_map>
#include <models/constraints/values/ConstraintValue.h>
#include <x-poly/utilities/List.h>
#include <x-poly/models/basic/Segment.h>
#include "models/constraints/structures/mapdata.h"

class Constraint{
public:
    enum Direction {Vertical, Horizontal, Total};
private:
    List<Point> constraints;
    ConstraintValue* v;
    Direction direction;
public:
    Constraint();
    Constraint(Point p, Direction d, ConstraintValue* value);
    Constraint(std::vector<Point> p, Direction d, ConstraintValue* value);
    Constraint(Segment<int> s, Direction d, ConstraintValue* value);
    Constraint(std::vector<Segment<int>> s, Direction d, ConstraintValue* value);

    double getValue(Point p);
    List<Point> getPoints();
    Direction getDirection();

};


#endif
