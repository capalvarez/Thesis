#include "Point.h"
#include <vector>

class Hole {
public:
    virtual Point getCenter() = 0;
    virtual std::vector<Segment*> getSegments() = 0;
};

