#include "../../../include/models/geometry/BreakableMesh.h"

BreakableMesh::BreakableMesh() {}

BreakableMesh::BreakableMesh(Mesh m) {
    this->mesh = m;
}

BrokenMeshInfo BreakableMesh::breakMesh(Segment<Point> crack) {
    return BrokenMeshInfo(std::vector<Polygon>(), std::vector<Polygon>(), Polygon());
}

