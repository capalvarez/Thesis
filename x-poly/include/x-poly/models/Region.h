#ifndef THESIS_REGION_H
#define THESIS_REGION_H

#include <vector>
#include <x-poly/models/basic/Segment.h>
#include <x-poly/models/hole/Hole.h>
#include <x-poly/models/polygon/Polygon.h>
#include <algorithm>
#include <x-poly/utilities/utilities.h>
#include <x-poly/models/generator/PointGenerator.h>
#include <climits>

class Region: public Polygon {
private:
    std::vector<Hole*> holes;
    std::vector<Point> p;
    std::vector<Point> seedPoints;

    void clean();
public:
    Region(std::vector<Point>& points);
    ~Region();

    std::vector<Point> getSeedPoints();
    std::vector<Hole*> getHoles();
    std::vector<Point> getRegionPoints();
    void addHole(Hole* h);
    void generatePoints(PointGenerator p, int nX, int nY);
    Rectangle getBox();
};

#endif
