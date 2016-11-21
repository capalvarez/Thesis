#include <x-poly/models/hole/clipper/ClipperWrapper.h>
#include <include/x-poly/utilities/Pair.h>
#include <algorithm>

ClipperLib::Paths ClipperWrapper::polyIntersection(std::vector<Point> parent, std::vector<Point> child, int maxScale) {
    ClipperLib::Path region, hole;
    ClipperLib::Paths solution;

    for(int i=0;i<parent.size(); i++){
        region << scalePoint(parent[i], maxScale);
    }

    for(int i=0;i<child.size();i++){
        hole << scalePoint(child[i], maxScale);
    }

    ClipperLib::Clipper clipper;
    clipper.AddPath(region, ClipperLib::ptSubject, true);
    clipper.AddPath(hole, ClipperLib::ptClip, true);
    clipper.Execute(ClipperLib::ctDifference, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

    return solution;
}

ClipperLib::Paths ClipperWrapper::polyUnion(std::vector<Polygon> polys, std::vector<Point> points, int maxScale) {
    ClipperLib::Paths polygons(polys.size());

    for (int i = 0; i < polys.size(); ++i) {
        std::vector<Point> polyPoints = polys[i].getPoints(points);

        for (int j = 0; j < polyPoints.size(); ++j) {
            polygons[i] << scalePoint(polyPoints[j], maxScale);
        }
    }

    ClipperLib::Paths mergedPolys;
    ClipperLib::Clipper clipper;

    clipper.AddPaths(polygons, ClipperLib::ptSubject, true);
    clipper.Execute(ClipperLib::ctUnion, mergedPolys, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

    return mergedPolys;
}

ClipperLib::IntPoint ClipperWrapper::scalePoint(Point point, int maxScale) {
    return ClipperLib::IntPoint((int)(maxScale*point.getX()), (int)(maxScale*point.getY()));
}

ClipperLib::Paths ClipperWrapper::polyUnion(Polygon p1, Polygon p2, std::vector<Point> points, int maxScale) {






}

