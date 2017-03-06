#ifndef THESIS_INDEXSEGMENTHASHER_H
#define THESIS_INDEXSEGMENTHASHER_H

#include <x-poly/models/basic/IndexSegment.h>

struct IndexSegmentHasher{
    std::size_t operator()(const IndexSegment &k) const {
        using std::size_t;
        using std::hash;

        return hash<int>()(k.getFirst()) + hash<int>()(k.getSecond());
    }
};



#endif 
