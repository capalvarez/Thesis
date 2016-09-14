#include "DOFS.h"

Pair<int> DOFS::addOuterDOF(Constraints constraints, std::vector<Point> points, int point_index, int type) {
    typename std::vector<int>::iterator it;
    it = std::find(occupied_point_indexes.begin(), occupied_point_indexes.end(), point_index);

    if(it!=occupied_point_indexes.end()){
        int outerDOF_index = (int) std::distance(occupied_point_indexes.begin(),it);

        return Pair<int>(outer_indexes[outerDOF_index], outer_indexes[outerDOF_index]+1);
    }

    int newIndex;
    if(type==0){
        newIndex = list.push_back(new VertexDOF(list.size(),point_index, DOF::Axis::x));

        list.push_back(new VertexDOF(list.size(), point_index, DOF::Axis::y));
    }else{
        newIndex = list.push_back(new EdgeDOF(list.size(),point_index, DOF::Axis::x));
        list.push_back(new EdgeDOF(list.size(), point_index, DOF::Axis::y));
    }

    constraints.addConstrainedDOF(points[point_index],newIndex,DOF::Axis::x);
    constraints.addConstrainedDOF(points[point_index],newIndex+1,DOF::Axis::y);

    occupied_point_indexes.push_back(point_index);
    outer_indexes.push_back(newIndex);

    return Pair<int>(newIndex, newIndex+1);
}


Pair<int> DOFS::addVertexDOF(Constraints constraints, std::vector<Point> points, int index) {
    return addOuterDOF(constraints, points, index, 0);
}

Pair<int> DOFS::addEdgeDOF(Constraints constraints, std::vector<Point> points, int index) {
    return addOuterDOF(constraints, points, index, 1);
}

Pair<int> DOFS::addInnerDOF(Pair<int> poly) {
    list.push_back(new InnerDOF(poly, list.size(), DOF::Axis::x));
    list.push_back(new InnerDOF(poly, list.size(), DOF::Axis::y));

    return Pair<int>(list.size() - 2, list.size() - 1);
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







