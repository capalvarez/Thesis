#include <algorithm>
#include "DOFS.h"
#include "VertexDOF.h"
#include "EdgeDOF.h"
#include "InnerDOF.h"

int DOFS::addOuterDOF(int point_index, int type) {
    typename std::vector<int>::iterator it;
    it = std::find(occupied_point_indexes.begin(), occupied_point_indexes.end(), point_index);

    if(it!=occupied_point_indexes.end()){
        int outerDOF_index = (int) std::distance(occupied_point_indexes.begin(),it);

        return outer_indexes[outerDOF_index];
    }

    int newIndex;
    if(type==0){
        newIndex = list.push_back(new VertexDOF(list.size(),point_index, DOF::Axis::x));
        list.push_back(new VertexDOF(list.size(), point_index, DOF::Axis::y));
    }else{
        newIndex = list.push_back(new EdgeDOF(list.size(),point_index, DOF::Axis::x));
        list.push_back(new EdgeDOF(list.size(), point_index, DOF::Axis::y));
    }

    occupied_point_indexes.push_back(point_index);
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
    list.push_back(new InnerDOF(poly, list.size(), DOF::Axis::x));
    list.push_back(new InnerDOF(poly, list.size(), DOF::Axis::y));

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







