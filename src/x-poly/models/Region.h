#ifndef THESIS_REGION_H
#define THESIS_REGION_H

#include <vector>
#include "models/basic/Segment.h"
#include "models/hole/Hole.h"
#include "models/polygon/Polygon.h"
#include <algorithm>
#include <utilities/utilities.h>
#include <models/generator/PointGenerator.h>
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
    void addHole(Hole* h);
    void generatePoints(PointGenerator p, int nX, int nY);
    Rectangle getBox();
};

#endif
