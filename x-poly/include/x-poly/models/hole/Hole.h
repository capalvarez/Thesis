#ifndef THESIS_HOLE_H
#define THESIS_HOLE_H

#include <x-poly/models/basic/Point.h>
#include <x-poly/models/basic/Segment.h>
#include <vector>
#include <x-poly/models/basic/IndexSegment.h>

class Hole {
protected:
    std::vector<Point> HolePoints;
    Point center;
    std::vector<IndexSegment> segments;
public:
    Hole(){};
    Hole(const Hole& other){
        this->center = other.center;
        this->HolePoints.assign(other.HolePoints.begin(), other.HolePoints.end());
        this->segments.assign(other.segments.begin(), other.segments.end());
    }

    virtual Point getCenter(){
        return this->center;
    };

    void getSegments(std::vector<IndexSegment>& s, int offset){
        for (IndexSegment seg: this->segments) {
            s.push_back(seg.add(offset));
        }
    };

    virtual std::vector<Point> getPoints(){
        return this->HolePoints;
    };

    std::string getString(){
        std::string result;

        result += center.getString() + "\n";

        result += utilities::toString(HolePoints.size()) + "\n";
        for (Point p: HolePoints) {
            result += p.getString() + "\n";
        }

        result += utilities::toString(segments.size()) + "\n";
        for (IndexSegment s: segments){
            result += s.getString() + "\n";
        }

        return result;
    }
};

#endif