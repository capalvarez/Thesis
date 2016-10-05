#ifndef THESIS_BREAKABLEMESH_H
#define THESIS_BREAKABLEMESH_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/Mesh.h>
#include <models/geometry/structures/BrokenMeshInfo.h>

class BreakableMesh : public Mesh{
private:
    Mesh mesh;
public:
    BreakableMesh();
    BreakableMesh(Mesh m);
    BrokenMeshInfo breakMesh(Segment<Point> crack);

};


#endif
