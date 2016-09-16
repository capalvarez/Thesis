#ifndef THESIS_CONSTRAINT_H
#define THESIS_CONSTRAINT_H

#include <veamy/models/constraints/structures/mapdata.h>
#include <unordered_map>

class Constraint {
public:
    enum Direction {Vertical, Horizontal, Total};

    virtual double getValue(Point p) = 0;
    virtual void addToMap(std::unordered_map<Point, Constraint*, PointHasher> map) = 0;
    Direction getDirection();

protected:
    Direction direction;
};

#endif
