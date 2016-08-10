#include <iostream>
#include <vector>
#include <x-poly/models/hole/lib/clipper.hpp>

using namespace std;

int main() {
    ClipperLib::Path polygon, hole;
    ClipperLib::Paths solution;
    polygon << ClipperLib::IntPoint(0,0) << ClipperLib::IntPoint(10,0) <<
               ClipperLib::IntPoint(10,10) << ClipperLib::IntPoint(0,10);
    hole << ClipperLib::IntPoint(2,0) << ClipperLib::IntPoint(7,0) <<
            ClipperLib::IntPoint(7,2) << ClipperLib::IntPoint(2,2);

    ClipperLib::Clipper clipper;
    clipper.AddPath(polygon, ClipperLib::ptSubject, true);
    clipper.AddPath(hole, ClipperLib::ptClip, true);
    clipper.Execute(ClipperLib::ctDifference, solution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

    std::cout << "hola";
}