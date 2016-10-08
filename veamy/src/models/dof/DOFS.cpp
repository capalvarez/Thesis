#include <veamy/models/dof/DOFS.h>

Pair<int> DOFS::addDOF(ConstraintsContainer &constraints, std::vector<Point> points, int point_index,
                       SegmentPair pair) {
    typename std::vector<int>::iterator it;
    it = std::find(occupied_point_indexes.begin(), occupied_point_indexes.end(), point_index);

    if(it!=occupied_point_indexes.end()){
        int outerDOF_index = (int) std::distance(occupied_point_indexes.begin(),it);

        return Pair<int>(outer_indexes[outerDOF_index], outer_indexes[outerDOF_index]+1);
    }

    int newIndex = list.push_back(new VertexDOF(list.size(),point_index, DOF::Axis::x));
    list.push_back(new VertexDOF(list.size(), point_index, DOF::Axis::y));

    constraints.addConstrainedDOF(newIndex,DOF::Axis::x, pair);
    constraints.addConstrainedDOF(newIndex+1,DOF::Axis::y, pair);

    occupied_point_indexes.push_back(point_index);
    outer_indexes.push_back(newIndex);

    return Pair<int>(newIndex, newIndex+1);
}

VeamyList<DOF *> DOFS::getDOFS() {
    return this->list;
}

int DOFS::size() {
    return list.size();
}

DOF *DOFS::get(int i) {
    return list.get(i);
}







