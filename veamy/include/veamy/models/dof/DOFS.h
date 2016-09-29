#ifndef THESIS_OUTERDOFS_H
#define THESIS_OUTERDOFS_H

#include <array>
#include <veamy/utilities/VeamyList.h>
#include <veamy/utilities/Pair.h>
#include <veamy/models/dof/VertexDOF.h>
#include <veamy/models/dof/EdgeDOF.h>
#include <veamy/models/dof/InnerDOF.h>
#include <algorithm>
#include <veamy/utilities/SegmentPair.h>
#include <veamy/models/constraints/ConstraintsContainer.h>

class DOFS {
private:
    VeamyList<DOF*> list;
    std::vector<int> occupied_point_indexes;
    std::vector<int> outer_indexes;

    Pair<int> addOuterDOF(ConstraintsContainer& constraints, std::vector<Point> points, int point_index, int type, SegmentPair pair);
public:
    Pair<int> addVertexDOF(ConstraintsContainer& constraints, std::vector<Point> points, int index, SegmentPair pair);
    Pair<int> addEdgeDOF(ConstraintsContainer& constraints, std::vector<Point> points, int index, SegmentPair pair);
    Pair<int> addInnerDOF(Pair<int> poly);

    VeamyList<DOF*> getDOFS();
    int size();
    DOF* get(int i);
};


#endif