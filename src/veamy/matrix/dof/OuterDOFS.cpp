#include <algorithm>
#include "OuterDOFS.h"
#include "VertexDOF.h"

int OuterDOFS::addVertexDOF(int index) {
    typename std::vector<int>::iterator it;
    it = std::find(occupied_indexes.begin(), occupied_indexes.end(), index);

    if(it!=occupied_indexes.end()){
        return (int) std::distance(occupied_indexes.begin(),it);
    }

    list.push_back(new VertexDOF(index));
    occupied_indexes.push_back(index);

    return (int) occupied_indexes.size() - 1;
}

int OuterDOFS::addEdgeDOF(int index) {
    return 0;
}

List<OuterDOF *> OuterDOFS::getDOFS() {
    return this->list;
}

int OuterDOFS::size() {
    return list.size();
}


OuterDOF *OuterDOFS::get(int i) {
    return list.get(i);
}







