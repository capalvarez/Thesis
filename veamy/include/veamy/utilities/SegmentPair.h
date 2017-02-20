#ifndef THESIS_SEGMENTPAIR_H
#define THESIS_SEGMENTPAIR_H

#include <x-poly/models/basic/IndexSegment.h>

struct SegmentPair{
    IndexSegment s1;
    IndexSegment s2;
    int number = 0;

    SegmentPair(IndexSegment seg1, IndexSegment seg2){
        s1 = seg1;
        s2 = seg2;
    }

    SegmentPair(IndexSegment seg){
        s1 = seg;
        number = 1;
    }
};

#endif
