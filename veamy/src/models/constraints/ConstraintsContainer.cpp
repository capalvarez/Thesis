#include <veamy/models/constraints/ConstraintsContainer.h>
#include <utilities/maputils.h>

ConstraintsContainer::ConstraintsContainer() {}

void ConstraintsContainer::addConstraints(NaturalConstraints c, PolygonalMesh mesh) {
    if(!areConsistent(c, this->essential, mesh)) {
        throw std::invalid_argument("Natural and essential boundary conditions can not intersect");
    }

    this->natural = c;
}

void ConstraintsContainer::addConstraints(EssentialConstraints c, PolygonalMesh mesh) {
    if(!areConsistent(this->natural, c, mesh)) {
        throw std::invalid_argument("Natural and essential boundary conditions can not intersect");
    }

    this->essential = c;
}

void ConstraintsContainer::addConstrainedDOF(std::vector<Point> points, int DOF_index, DOF::Axis axis, SegmentPair pair) {
    natural.addConstrainedDOF(points, DOF_index,axis,pair);
    essential.addConstrainedDOF(points, DOF_index,axis,pair);
}

EssentialConstraints ConstraintsContainer::getEssentialConstraints() {
    return essential;
}

NaturalConstraints ConstraintsContainer::getNaturalConstraints() {
    return natural;
}

bool ConstraintsContainer::areConsistent(NaturalConstraints n, EssentialConstraints e, PolygonalMesh mesh) {
    Point inter;
    std::vector<IndexSegment> naturalSegments;
    std::transform(n.getConstrainedSegments().begin(), n.getConstrainedSegments().end(), std::back_inserter(naturalSegments), map_utils::GetKeys());

    std::vector<IndexSegment> essentialSegments;
    std::transform(e.getConstrainedSegments().begin(), e.getConstrainedSegments().end(), std::back_inserter(essentialSegments), map_utils::GetKeys());

    for (int i = 0; i < naturalSegments.size(); ++i) {
        for (int j = 0; j < essentialSegments.size(); ++j) {
            if(naturalSegments[i].intersection(mesh.getPoints().getList(),essentialSegments[j],inter)){
                return false;
            }
        }
    }

    return true;
}

