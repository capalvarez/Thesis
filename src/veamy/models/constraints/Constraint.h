#ifndef THESIS_CONSTRAINT_H
#define THESIS_CONSTRAINT_H

class Constraint {
public:
    enum ConstraintDirection {Vertical, Horizontal, Total};

    virtual void addToMap(std::unordered_map<Point,int,PointHasher> map) = 0;
};

#endif
