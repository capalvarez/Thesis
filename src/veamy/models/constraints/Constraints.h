#ifndef THESIS_CONSTRAINTS_H
#define THESIS_CONSTRAINTS_H

#include <x-poly/models/basic/Point.h>
#include <unordered_map>
#include <vector>
#include <x-poly/utilities/List.h>
#include "Constraint.h"
#include "structures/mapdata.cpp"

class Constraints {
private:
    std::unordered_map<Point, int, PointHasher> constrained_points;
    List<int> constrained_dofs;
public:
    Constraints();
    void addConstraint(Constraint* c);
    bool isConstrained(Point p);

    std::vector<int> getConstrainedDOF();
    void addConstrainedDOF(int DOF_index);
};


#endif
