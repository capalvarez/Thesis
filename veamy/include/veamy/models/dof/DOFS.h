#ifndef THESIS_DOFS_H
#define THESIS_DOFS_H

#include <array>
#include <veamy/utilities/VeamyList.h>
#include <veamy/utilities/Pair.h>
#include <algorithm>
#include <veamy/utilities/SegmentPair.h>
#include <veamy/models/constraints/ConstraintsContainer.h>

class DOFS {
private:
    VeamyList<DOF> list;
    std::vector<int> occupied_point_indexes;
    std::vector<int> outer_indexes;
public:
    Pair<int> addDOF(ConstraintsContainer &constraints, std::vector<Point> points, int point_index,
                     SegmentPair<int> pair);
    VeamyList<DOF> getDOFS();
    int size();
    DOF get(int i);
};


#endif
