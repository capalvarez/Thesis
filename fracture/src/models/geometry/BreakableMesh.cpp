#include <fracture/models/geometry/BreakableMesh.h>

BreakableMesh::BreakableMesh() {}

BreakableMesh::BreakableMesh(Mesh m) {
    this->mesh = m;
}

BrokenMeshInfo BreakableMesh::breakMesh(int init, Segment<Point> crack) {
    NeighbourInfo n1 = getNeighbour(init, crack);
    Polygon poly1 = getPolygon(n1.neighbour);

    while(true){
        if(poly1.containsPoint(this->points, crack.getSecond())){
            break;
        }

        NeighbourInfo n2 = getNeighbour(n1.neighbour, crack);




    }







}


