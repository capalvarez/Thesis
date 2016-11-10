#ifndef THESIS_BREAKABLEMESH_H
#define THESIS_BREAKABLEMESH_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/Mesh.h>
#include <fracture/geometry/structures/PolygonChangeData.h>


class BreakableMesh : public Mesh{
private:

    void mergePolygons(int i1, int i2);


public:
    BreakableMesh();
    BreakableMesh(const Mesh& m);
    PolygonChangeData breakMesh(int init, Segment<Point> crack);
    void swapPolygons(int first, int last);

};


#endif
