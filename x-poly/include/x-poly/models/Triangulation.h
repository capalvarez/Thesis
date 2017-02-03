#ifndef THESIS_TRIANGULATION_H
#define THESIS_TRIANGULATION_H

#include <vector>
#include <string>
#include <fstream>
#include <x-poly/models/polygon/Triangle.h>
#include <x-poly/voronoi/structures/SegmentMap.h>

class Triangulation : public Mesh{
private:
    std::vector<Triangle> triangles;
public:
    Triangulation(std::vector<Point>& p, std::vector<Triangle>& t, SegmentMap edges);

    std::vector<Triangle> getTriangles();

};

#endif
