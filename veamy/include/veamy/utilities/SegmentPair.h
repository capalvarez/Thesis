#ifndef THESIS_SEGMENTPAIR_H
#define THESIS_SEGMENTPAIR_H

struct SegmentPair{
    Segment s1;
    Segment s2;
    int number = 0;

    SegmentPair(Segment seg1, Segment seg2){
        s1 = seg1;
        s2 = seg2;
    }

    SegmentPair(Segment seg){
        s1 = seg;
        number = 1;
    }
};

#endif
