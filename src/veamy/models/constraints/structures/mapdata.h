#ifndef MAPDATA_H
#define MAPDATA_H

struct SegmentHasher {
    std::size_t operator()(const Segment &k) const {
        using std::size_t;
        using std::hash;

        return hash<int>()(k.getFirst()) + hash<int>()(k.getSecond());
    }
};

struct intHasher {
    std::size_t operator()(const int &k) const {
        using std::size_t;
        using std::hash;

        return hash<int>()(k);
    }
};

#endif
