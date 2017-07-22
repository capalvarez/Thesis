#ifndef THESIS_TRIANGULATION_H
#define THESIS_TRIANGULATION_H

#include <vector>
#include <string>
#include <fstream>
#include <x-poly/models/polygon/Triangle.h>
#include <x-poly/models/neighbourhood/SegmentMap.h>
#include <x-poly/models/Mesh.h>

class Triangulation : public Mesh {
private:
    std::vector<Triangle> triangles;
    std::vector<Point> points;
public:
    Triangulation(std::vector<Point>& p, std::vector<Triangle>& t, SegmentMap edges);
    std::vector<Triangle> getTriangles();
    void print(std::string fileName);
    void writeElements(std::ofstream& file);
    std::vector<Point> getPoints();
};

#endif
