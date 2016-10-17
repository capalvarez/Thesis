#ifndef THESIS_SEGMENTMAP_H
#define THESIS_SEGMENTMAP_H

#include <x-poly/models/basic/Segment.h>
#include <x-poly/voronoi/structures/mapdata.h>
#include <x-poly/utilities/Pair.h>
#include <unordered_map>

class SegmentMap{
private:
    std::unordered_map<Segment<int>,Pair<int>,SegmentHasher> map;
public:
    SegmentMap();
    void insert(Segment<int> s, Pair<int>& p);
    Pair<int>& get(Segment<int> s);
    std::unordered_map<Segment<int>,Pair<int>,SegmentHasher>& getMap();
};

#endif 
