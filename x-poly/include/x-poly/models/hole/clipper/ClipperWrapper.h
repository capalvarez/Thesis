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
};


#endif
