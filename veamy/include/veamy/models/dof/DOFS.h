#ifndef THESIS_DOFS_H
#define THESIS_DOFS_H

#include <array>
#include <algorithm>
#include <veamy/utilities/SegmentPair.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/utilities/hash/veamyhashfunctions.h>

class DOFS {
private:
    UniqueList<DOF> list;
    std::vector<int> occupied_point_indexes;
    std::vector<int> outer_indexes;

    std::unordered_map<int, Pair<int>> point_to_dofs;
public:
    Pair<int> addDOF(ConstraintsContainer &constraints, std::vector<Point> points, int point_index,
                     SegmentPair pair);
    UniqueList<DOF> getDOFS();
    int size();
    DOF get(int i);

    Pair<int> pointToDOFS(int point);
};


#endif
