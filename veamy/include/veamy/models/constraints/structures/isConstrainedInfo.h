#ifndef THESIS_ISCONSTRAINEDINFO_H
#define THESIS_ISCONSTRAINEDINFO_H

#include <x-poly/models/basic/IndexSegment.h>

struct isConstrainedInfo{
    bool isConstrained;
    IndexSegment container;

    isConstrainedInfo(IndexSegment c){
        isConstrained = true;
        container = c;
    }

    isConstrainedInfo(){
        isConstrained = false;
    }
};


#endif
