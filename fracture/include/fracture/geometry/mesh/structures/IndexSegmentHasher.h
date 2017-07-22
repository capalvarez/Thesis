#ifndef THESIS_INDEXSEGMENTHASHER_H
#define THESIS_INDEXSEGMENTHASHER_H

#include <x-poly/models/basic/IndexSegment.h>

struct IndexSegmentHasher{
    std::size_t operator()(const IndexSegment &k) const {
        using std::size_t;
        using std::hash;

        return utilities::hash32(k.getFirst()) + utilities::hash32(k.getSecond());
    }
};



#endif 
