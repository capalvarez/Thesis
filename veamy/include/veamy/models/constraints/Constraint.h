#ifndef THESIS_POINTCONSTRAINT_H
#define THESIS_POINTCONSTRAINT_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <unordered_map>
#include <veamy/models/constraints/values/ConstraintValue.h>
#include <x-poly/models/basic/Segment.h>
#include <utilities/UniqueList.h>
#include <utilities/Pair.h>

class Constraint{
public:
    enum Direction {Vertical, Horizontal, Total};
private:
    UniqueList<Segment<int>> constraints;
    ConstraintValue* v;
    Direction direction;

    Segment<int> fromPointToInt(Segment<Point> s, std::vector<Point> points);
public:
    Constraint();
    Constraint(Segment<int> s, Direction d, ConstraintValue* value);
    Constraint(std::vector<Segment<int>> s, Direction d, ConstraintValue* value);
    Constraint(Segment<Point> s, std::vector<Point> points, Direction d, ConstraintValue* value);
    Constraint(std::vector<Segment<Point>> s, std::vector<Point> points, Direction d, ConstraintValue* value);

    double getValue(Point p);
    UniqueList<Segment<int>> getSegments();
    Direction getDirection();

    Pair<int> getIndex(int point_index);

};


#endif
