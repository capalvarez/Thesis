#ifndef THESIS_HOLE_H
#define THESIS_HOLE_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <vector>
#include <x-poly/models/basic/IndexSegment.h>

class Hole {
protected:
    std::vector<Point> HolePoints;
public:
    virtual Point getCenter() = 0;
    virtual void getSegments(std::vector<IndexSegment>& segments, int offset) = 0;
    virtual std::vector<Point> getPoints(){
        return this->HolePoints;
    };
};

#endif