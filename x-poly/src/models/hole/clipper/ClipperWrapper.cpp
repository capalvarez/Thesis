#include <x-poly/models/hole/clipper/ClipperWrapper.h>

ClipperLib::Paths ClipperWrapper::polyIntersection(std::vector<Point> parent, std::vector<Point> child, int maxScale) {
    ClipperLib::Path region, hole;
    ClipperLib::Paths solution;

    for(int i=0;i<parent.size(); i++){
        region << ClipperLib::IntPoint((int)(maxScale*parent[i].getX()), (int)(maxScale*parent[i].getY()));
    }

    for(int i=0;i<child.size();i++){
        hole << ClipperLib::IntPoint((int)(maxScale*child[i].getX()), (int)(maxScale*child[i].getY()));
    }

    ClipperLib::Clipper clipper;
    clipper.AddPath(region, ClipperLib::ptSubject, true);
    clipper.AddPath(hole, ClipperLib::ptClip, true);
    clipper.Execute(ClipperLib::ctDifference, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

    return solution;
}

ClipperLib::Paths ClipperWrapper::polyUnion(std::vector<Polygon> polys, std::vector<Point> points) {
    return ClipperLib::Paths();
}
