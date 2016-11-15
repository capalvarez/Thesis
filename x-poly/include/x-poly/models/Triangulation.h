#ifndef THESIS_TRIANGULATION_H
#define THESIS_TRIANGULATION_H

#include <vector>
#include <string>
#include <fstream>
#include <x-poly/models/polygon/Triangle.h>
#include <x-poly/voronoi/structures/SegmentMap.h>

class Triangulation {
private:
    std::vector<Triangle> triangles;
    std::vector<Point> points;
    SegmentMap edgeMap;
public:
    Triangulation(std::vector<Point> p, std::vector<Triangle> t, SegmentMap edges);
    void writeInFile(std::string fileName);

    std::vector<Point> getPoints();
    SegmentMap getSegments();
};

#endif
