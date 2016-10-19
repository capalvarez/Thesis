#ifndef CONSTRAINMAPDATA_H
#define CONSTRAINMAPDATA_H

#include <x-poly/models/basic/Segment.h>

struct intHasher {
    std::size_t operator()(const int &k) const {
        using std::size_t;
        using std::hash;

        return hash<int>()(k);
    }
};

#endif
