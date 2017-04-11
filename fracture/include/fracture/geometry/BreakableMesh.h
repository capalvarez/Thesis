#ifndef THESIS_BREAKABLEMESH_H
#define THESIS_BREAKABLEMESH_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/PolygonalMesh.h>
#include <fracture/geometry/structures/PolygonChangeData.h>


class BreakableMesh : public PolygonalMesh{
public:
    BreakableMesh();
    BreakableMesh(const PolygonalMesh& m);

    PolygonChangeData breakMesh(int init, PointSegment crack);
    void splitPolygons(NeighbourInfo n1, NeighbourInfo n2, int init, std::vector<Polygon> &oldPolygons,
                       std::vector<Polygon> &newPolygons);

    void swapPolygons(int first, int last);
    void mergePolygons(int i1, int i2);
    int mergePolygons(std::vector<int> polys);
    bool areMergeable(Polygon poly1, int poly2);
};


#endif
