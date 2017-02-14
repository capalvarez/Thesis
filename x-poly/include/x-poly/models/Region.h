#ifndef THESIS_REGION_H
#define THESIS_REGION_H

#include <vector>
#include <x-poly/models/basic/Segment.h>
#include <x-poly/models/hole/Hole.h>
#include <x-poly/models/polygon/Polygon.h>
#include <algorithm>
#include <x-poly/utilities/xpolyutilities.h>
#include <x-poly/models/generator/PointGenerator.h>
#include <climits>
#include <x-poly/models/hole/PolygonalHole.h>
#include <x-poly/models/hole/clipper/lib/clipper.hpp>
#include <x-poly/models/hole/clipper/ClipperWrapper.h>

class Region: public Polygon {
private:
    std::vector<Hole*> holes;
    std::vector<Point> p;
    std::vector<Point> seedPoints;
    int maxScale;

    void clean();
public:
    Region(std::vector<Point>& points);
    Region();
    Region(const Region& other);
    ~Region();

    void mutate(std::vector<Point>& points);
    std::vector<Point> getSeedPoints();
    std::vector<Point> getRegionPoints();
    std::vector<Hole*> getHoles();
    void addHole(Hole* h);
    void generatePoints(PointGenerator p, int nX, int nY);
    BoundingBox getBox();
    void getSegments(std::vector<IndexSegment>& s);
    bool containsPoint(Point p);

};

#endif
