#include "models/basic/Point.h"
#include "models/basic/Segment.h"
#include <vector>

class Hole {
public:
    virtual Point getCenter() = 0;
    virtual void getSegments(std::vector<Segment> segments) = 0;
};

