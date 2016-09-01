#ifndef THESIS_OUTERDOFS_H
#define THESIS_OUTERDOFS_H

#include <array>
#include <x-poly/utilities/List.h>
#include "OuterDOF.h"

class DOFS {
private:
    List<DOF*> list;
    std::vector<int> occupied_point_indexes;
    std::vector<int> outer_indexes;

    int addOuterDOF(int index, int type);
public:
    int addVertexDOF(int index);
    int addEdgeDOF(int index);
    int addInnerDOF(Pair<int> poly);

    List<DOF*> getDOFS();
    int size();
    DOF* get(int i);
};


#endif
