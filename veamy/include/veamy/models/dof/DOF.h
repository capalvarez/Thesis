#ifndef THESIS_DOF_H
#define THESIS_DOF_H

#include "../../../../../utilities/include/utilities/Pair.h"
#include <x-poly/models/polygon/Polygon.h>

class DOF {
public:
    enum Axis {x, y};

    DOF(int index, int point_index, DOF::Axis a);
    int globalIndex() const;
    int pointIndex();
    bool operator==(const DOF& other) const;
    bool operator<(const DOF& other) const;
protected:
    int index;
    int point_index;
    DOF::Axis d;
};


#endif
