#ifndef THESIS_DEADCRACKTIP_H
#define THESIS_DEADCRACKTIP_H

#include <fracture/models/crack/CrackTip.h>

class DeadCrackTip : public CrackTip {
public:
    bool isFinished();
};


#endif
