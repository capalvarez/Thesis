#ifndef THESIS_BREAKABLEMESH_H
#define THESIS_BREAKABLEMESH_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/PolygonalMesh.h>
#include <fracture/geometry/structures/PolygonChangeData.h>


class BreakableMesh : public PolygonalMesh{
public:
    BreakableMesh();
    BreakableMesh(const PolygonalMesh& m);

    PolygonChangeData breakMesh(int init, PointSegment crack, bool initialCrackTip, UniqueList<Pair<int>> &newPoints);
    PolygonChangeData breakMesh(int init, PointSegment crack, bool initialCrackTip, UniqueList<Pair<int>> &newPoints,
                                std::vector<int> previous);
    void breakPolygons(NeighbourInfo n1, NeighbourInfo &n2, int init, std::vector<Polygon> &oldPolygons,
                           std::vector<Polygon> &newPolygons, UniqueList<Pair<int>> &newPoints);
    void splitPolygons(NeighbourInfo n1, NeighbourInfo &n2, int init, std::vector<Polygon> &oldPolygons,
                       std::vector<Polygon> &newPolygons);
    Pair<int> computeNewPolygons(NeighbourInfo n1, NeighbourInfo &n2, Polygon poly1, std::vector<Polygon> &newPolygons,
                                 std::vector<int> &new1, std::vector<int> &new2, int p1, int p2, int init, int p3,
                                 int p4);

    void swapPolygons(int first, int last, std::unordered_map<IndexSegment,int,SegmentHasher>& toIgnore);
    void mergePolygons(int i1, int i2);
    int mergePolygons(std::vector<int> &polys);
    bool areMergeable(Polygon poly1, int poly2);
    std::vector<int> getUnusedPoints(std::vector<int> allPoints, std::vector<int> merged);
    std::vector<int> getAllPoints(std::vector<int> polys);
};


#endif
