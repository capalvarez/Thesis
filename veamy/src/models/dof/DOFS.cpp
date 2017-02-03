#include <veamy/models/dof/DOFS.h>

Pair<int> DOFS::addDOF(ConstraintsContainer &constraints, std::vector<Point> points, int point_index,
                       SegmentPair<int> pair) {
    typename std::vector<int>::iterator it;
    it = std::find(occupied_point_indexes.begin(), occupied_point_indexes.end(), point_index);

    if(it!=occupied_point_indexes.end()){
        int outerDOF_index = (int) std::distance(occupied_point_indexes.begin(),it);

        return Pair<int>(outer_indexes[outerDOF_index], outer_indexes[outerDOF_index]+1);
    }

    DOF newDOF = DOF(list.size(),point_index, DOF::Axis::x);
    DOF newDOF2 = DOF(list.size(),point_index, DOF::Axis::y);

    int newIndex = list.push_back(newDOF);
    list.push_back(newDOF2);

    constraints.addConstrainedDOF(points, newIndex, DOF::Axis::x, pair);
    constraints.addConstrainedDOF(points, newIndex+1, DOF::Axis::y, pair);

    occupied_point_indexes.push_back(point_index);
    outer_indexes.push_back(newIndex);

    //TODO: Check memory usage here
    Pair<int> dofPair(newIndex, newIndex+1);
    point_to_dofs.insert(std::make_pair(point_index, dofPair));

    return dofPair;
}

UniqueList<DOF> DOFS::getDOFS() {
    return this->list;
}

int DOFS::size() {
    return list.size();
}

DOF DOFS::get(int i) {
    return list.get(i);
}

Pair<int> DOFS::pointToDOFS(int point) {
    return this->point_to_dofs[point];
}





