#ifndef THESIS_MESH_H
#define THESIS_MESH_H

#include <x-poly/models/neighbourhood/SegmentMap.h>
#include <utilities/UniqueList.h>
#include <fstream>

class Mesh{
protected:
    SegmentMap edges;
    UniqueList<Point> points;
public:
    void printInFile(std::string fileName);
    virtual void writeElements(std::ofstream& file) = 0;

    SegmentMap& getSegments();
    SegmentMap getSegments() const ;

    UniqueList<Point>& getPoints();
    UniqueList<Point> getPoints() const;

    bool isFull();
};


#endif