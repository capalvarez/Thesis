#ifndef THESIS_TRIANGULATION_H
#define THESIS_TRIANGULATION_H

#include <vector>
#include <string>
#include <fstream>
#include <x-poly/models/polygon/Triangle.h>

class Triangulation {
private:
    std::vector<Triangle> triangles;
    std::vector<Point> points;
public:
    Triangulation(std::vector<Point>& p, std::vector<Triangle>& t);
    void writeInFile(std::string fileName);
};

#endif
