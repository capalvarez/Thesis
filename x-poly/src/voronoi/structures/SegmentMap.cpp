#include <x-poly/voronoi/structures/SegmentMap.h>

SegmentMap::SegmentMap() {}

void SegmentMap::insert(Segment<int> s, Pair<int> &p) {
    std::unordered_map<Segment<int>,Pair<int>,SegmentHasher>::const_iterator got = this->map.find (s);

    if(got == this->map.end()){
        this->map.insert(std::make_pair(s,p));
    }
}

Pair<int>& SegmentMap::get(Segment<int> s) {
    return map[s];
}

std::unordered_map<Segment<int>, Pair<int>, SegmentHasher>& SegmentMap::getMap() {
    return this->map;
}
