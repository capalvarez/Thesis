#ifndef THESIS_ISCONSTRAINEDINFO_H
#define THESIS_ISCONSTRAINEDINFO_H

#include <x-poly/models/basic/Segment.h>

struct isConstrainedInfo{
    bool isConstrained;
    Segment<int> container;

    isConstrainedInfo(Segment<int> c){
        isConstrained = true;
        container = c;
    }

    isConstrainedInfo(){
        isConstrained = false;
    }
};


#endif
