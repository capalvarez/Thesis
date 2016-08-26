#include <algorithm>
#include "DOFS.h"
#include "VertexDOF.h"
#include "EdgeDOF.h"
#include "InnerDOF.h"

int DOFS::addVertexDOF(int index) {
    typename std::vector<int>::iterator it;
    it = std::find(occupied_indexes.begin(), occupied_indexes.end(), index);

    if(it!=occupied_indexes.end()){
        return (int) std::distance(occupied_indexes.begin(),it);
    }

    list.push_back(new VertexDOF(index));
    occupied_indexes.push_back(index);

    return (int) occupied_indexes.size() - 1;
}

int DOFS::addEdgeDOF(int index) {
    typename std::vector<int>::iterator it;
    it = std::find(occupied_indexes.begin(), occupied_indexes.end(), index);

    if(it!=occupied_indexes.end()){
        return (int) std::distance(occupied_indexes.begin(),it);
    }

    list.push_back(new EdgeDOF(index));
    occupied_indexes.push_back(index);

    return (int) occupied_indexes.size() - 1;
}


int DOFS::addInnerDOF(Pair<int> poly) {
    list.push_back(new InnerDOF(poly, occupied_indexes.size()));
    occupied_indexes.push_back(occupied_indexes.size());

    return (int) occupied_indexes.size() - 1;
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







