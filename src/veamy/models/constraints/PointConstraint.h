#ifndef THESIS_POINTCONSTRAINT_H
#define THESIS_POINTCONSTRAINT_H

#include <x-poly/models/basic/Point.h>
#include <vector>
#include <unordered_map>
#include "Constraint.h"
#include "structures/mapdata.cpp"

class PointConstraint : public Constraint{
private:
    //TODO: Check if the user repeats constrained_points
    std::vector<Point> constraints;
public:
    PointConstraint(Point p, Direction d);
    PointConstraint(std::vector<Point> p, Direction d);

    void addToMap(std::unordered_map<Point,int,PointHasher> map);
};


#endif
