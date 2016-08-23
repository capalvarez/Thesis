#ifndef THESIS_OUTERDOFS_H
#define THESIS_OUTERDOFS_H

#include <array>
#include <x-poly/utilities/List.h>
#include "OuterDOF.h"

class OuterDOFS {
private:
    List<OuterDOF*> list;
    std::vector<int> occupied_indexes;
public:
    int addVertexDOF(int index);
    int addEdgeDOF(int index);

    List<OuterDOF*> getDOFS();
    int size();
    OuterDOF* get(int i);
};


#endif
