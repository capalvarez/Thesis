#ifndef THESIS_MESH_H
#define THESIS_MESH_H

#include <x-poly/voronoi/structures/SegmentMap.h>

class Mesh{
protected:
    SegmentMap edges;
    UniqueList<Point> points;
public:
    void printInFile(std::string fileName);

    SegmentMap& getSegments();
    SegmentMap getSegments() const ;

    UniqueList<Point>& getPoints();
    UniqueList<Point> getPoints() const;
};


#endif