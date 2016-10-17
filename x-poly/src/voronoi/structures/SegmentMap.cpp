#include <x-poly/voronoi/structures/SegmentMap.h>

SegmentMap::SegmentMap() {}

void SegmentMap::insert(Segment<int> s, int polygonIndex) {
    std::unordered_map<Segment<int>,Neighbours,SegmentHasher>::iterator got = this->map.find(s);

    if(got == this->map.end()){
        Neighbours n (polygonIndex);
        this->map.insert(std::make_pair(s,n));
    }else{
        got->second.setNeighbour(polygonIndex);
    }
}

Neighbours& SegmentMap::get(Segment<int> s) {
    return map[s];
}

std::unordered_map<Segment<int>,Neighbours, SegmentHasher>& SegmentMap::getMap() {
    return this->map;
}
