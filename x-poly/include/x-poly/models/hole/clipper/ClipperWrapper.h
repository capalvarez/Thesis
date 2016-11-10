#ifndef THESIS_CLIPPERWRAPPER_H
#define THESIS_CLIPPERWRAPPER_H

#include <x-poly/models/hole/clipper/lib/clipper.hpp>
#include <x-poly/models/basic/Point.h>
#include <x-poly/models/polygon/Polygon.h>

class ClipperWrapper {
private:
    static ClipperLib::IntPoint scalePoint(Point point, int maxScale);
public:
    static ClipperLib::Paths polyIntersection(std::vector<Point> parent, std::vector<Point> child, int maxScale);
    static ClipperLib::Paths polyUnion(std::vector<Polygon> polys, std::vector<Point> points, int maxScale);
    static ClipperLib::Paths polyUnion(Polygon p1, Polygon p2, std::vector<Point> points, int maxScale);
};


#endif
