#ifndef THESIS_SEGMENTMAP_H
#define THESIS_SEGMENTMAP_H

#include <x-poly/models/basic/Segment.h>
#include <x-poly/voronoi/structures/mapdata.h>
#include <x-poly/utilities/Pair.h>
#include <unordered_map>
#include "Neighbours.h"

class SegmentMap{
private:
    std::unordered_map<Segment<int>,Neighbours,SegmentHasher> map;
public:
    SegmentMap();
    void insert(Segment<int> s, int polygonIndex);
    Neighbours& get(Segment<int> s);
    std::unordered_map<Segment<int>,Neighbours,SegmentHasher>& getMap();
};

#endif 
