#include <algorithm>
#include "DOFS.h"
#include "VertexDOF.h"
#include "EdgeDOF.h"
#include "InnerDOF.h"

int DOFS::addOuterDOF(int index, int type) {
    typename std::vector<int>::iterator it;
    it = std::find(occupied_point_indexes.begin(), occupied_point_indexes.end(), index);

    if(it!=occupied_point_indexes.end()){
        int outerDOF_index = (int) std::distance(occupied_point_indexes.begin(),it);

        return outer_indexes[outerDOF_index];
    }

    int newIndex;
    if(type==0){
        newIndex = list.push_back(new VertexDOF(index));
    }else{
        newIndex = list.push_back(new EdgeDOF(index));
    }

    occupied_point_indexes.push_back(index);
    outer_indexes.push_back(newIndex);

    return newIndex;
}


int DOFS::addVertexDOF(int index) {
    return addOuterDOF(index, 0);
}

int DOFS::addEdgeDOF(int index) {
    return addOuterDOF(index, 1);
}


int DOFS::addInnerDOF(Pair<int> poly) {
    list.push_back(new InnerDOF(poly, list.size()));

    return list.size() - 1;
}

List<DOF *> DOFS::getDOFS() {
    return this->list;
}

int DOFS::size() {
    return list.size();
}

DOF *DOFS::get(int i) {
    return list.get(i);
}







