#ifndef THESIS_OUTERDOFS_H
#define THESIS_OUTERDOFS_H

#include <array>
#include <x-poly/utilities/List.h>
#include <veamy/utilities/Pair.h>
#include <veamy/models/dof/VertexDOF.h>
#include <veamy/models/dof/EdgeDOF.h>
#include <veamy/models/dof/InnerDOF.h>
#include <algorithm>
#include <veamy/models/constraints/EssentialConstraints.h>
#include <utilities/SegmentPair.h>

class DOFS {
private:
    List<DOF*> list;
    std::vector<int> occupied_point_indexes;
    std::vector<int> outer_indexes;

    Pair<int> addOuterDOF(EssentialConstraints& constraints, std::vector<Point> points, int point_index, int type, SegmentPair pair);
public:
    Pair<int> addVertexDOF(EssentialConstraints& constraints, std::vector<Point> points, int index, SegmentPair pair);
    Pair<int> addEdgeDOF(EssentialConstraints& constraints, std::vector<Point> points, int index, SegmentPair pair);
    Pair<int> addInnerDOF(Pair<int> poly);

    List<DOF*> getDOFS();
    int size();
    DOF* get(int i);
};


#endif
