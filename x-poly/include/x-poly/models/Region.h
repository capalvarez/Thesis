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
#include <x-poly/config/XPolyConfig.h>

class Region: public Polygon {
private:
    std::vector<Hole> holes;
    std::vector<Point> p;
    std::vector<Point> seedPoints;

    void clean();
public:
    Region(std::vector<Point>& points);
    Region();
    Region(const Polygon& other, std::vector<Point>& points);
    Region(const Region& other);
    ~Region();

    void mutate(std::vector<Point>& points);
    std::vector<Point> getSeedPoints();
    std::vector<Point> getRegionPoints();
    std::vector<Hole>& getHoles();
    void addHole(Hole h);
    void generateSeedPoints(PointGenerator p, int nX, int nY);
    void addSeedPoints(std::vector<Point> seeds);
    BoundingBox getBox();
    void getSegments(std::vector<IndexSegment>& s);
    bool containsPoint(Point p);
    bool inEdges(Point p);
    void cleanSeedPoints();
    void replaceSegment(PointSegment segment, std::vector<Point> points);
};

#endif
