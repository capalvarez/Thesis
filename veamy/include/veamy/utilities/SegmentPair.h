#ifndef THESIS_SEGMENTPAIR_H
#define THESIS_SEGMENTPAIR_H

#include <x-poly/models/basic/Segment.h>

template <typename T>
struct SegmentPair{
    Segment<T> s1;
    Segment<T> s2;
    int number = 0;

    SegmentPair(Segment<T> seg1, Segment<T> seg2){
        s1 = seg1;
        s2 = seg2;
    }

    SegmentPair(Segment<T> seg){
        s1 = seg;
        number = 1;
    }
};


template struct SegmentPair<int>;
template struct SegmentPair<Point>;

#endif
