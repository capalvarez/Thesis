#ifndef THESIS_BREAKABLEMESH_H
#define THESIS_BREAKABLEMESH_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/Mesh.h>
#include <fracture/models/geometry/structures/BrokenMeshInfo.h>

class BreakableMesh : public Mesh{
private:
    Mesh mesh;
public:
    BreakableMesh();
    BreakableMesh(Mesh m);
    BrokenMeshInfo breakMesh(int init, Segment<Point> crack);

};


#endif
